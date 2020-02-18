
#include <fstream>
#include <iostream>
#include "buildus.h"
#include <sstream>
#include <string>
#include <vector>

bool getConfig(std::string argv1) {
    // Recuperer le chemin actuel
	auto path = boost::filesystem::current_path();

	// Lire le fichier 'index'
	std::ifstream config(argv1);

    // Variables de stockage
    std::string noun_exe;

    std::vector<std::string> include_dir;

    std::vector<std::string> library_dir;
    std::vector<std::string> list_libs;

    std::vector<std::string> association(2);
    std::vector< std::vector<std::string> > list_asso;

    std::vector<std::string> list_files;

    if(config) {
        std::string line;
        bool isCompile = false;
        bool isInclude = false;
        bool isLibrary = false;
        bool isLibs    = false;

        while(getline(config, line)){
            // Recuperer le nom de l'executable --------------------
            if(line.find("projet") != std::string::npos) {
                std::cout << "nom de l'executable : " << line.substr(line.find(' ') + 1, -1) << std::endl;
                
                noun_exe = line.substr(line.find(' ') + 1, -1).c_str();
            }
            // -----------------------------------------------------

            // Recuperer les includes ------------------------------
            if(isInclude) {
                if(line.find("var") != std::string::npos) {
                    include_dir.push_back(line.substr(line.find(' ') + 1, -1));
     
                }else {
                    isInclude = false;
                }
                
            }

            if(line.find("deps_include") != std::string::npos) {
                isInclude = true;
            }
            // -----------------------------------------------------

            // Recuperer les libraires -----------------------------
            if(isLibrary) {
                if(line.find("var") != std::string::npos) {
                    library_dir.push_back(line.substr(line.find(' ') + 1, -1));

                }else if(isLibs) {
                    list_libs.push_back(line.substr(line.find('-') + 1, -1));
                
                }else if(line.find("libs") != std::string::npos) {
                    isLibs = true;

                }else {
                    isLibrary = false;
                    isLibs    = false;

                }
            }

            if(line.find("deps_library") != std::string::npos) {
                isLibrary = true;
            }
            // -----------------------------------------------------

            // Recuperer l'association entre variable et fichier ---
            if(isCompile){
                if(line.find("-") != std::string::npos) {
                    association[0] = line.substr(line.find('-') + 1, line.find(':') - 1);
                    association[1] = line.substr(line.find(':') + 1, -1);
                    
                    std::cout << "liste : " << association[0] << " >> " << association[1] << std::endl;

                    list_asso.push_back(association);

                    std::cout << list_asso.size() << std::endl;
                
                }else {
                    isCompile = false;
                }
            }

            if(line.find("compile") != std::string::npos) {
                isCompile = true;
            }
            // -----------------------------------------------------

            // Recuperer les fichiers a utiliser -------------------
            if(line.find("package") != std::string::npos) {
                std::cout << "fichiers utilises : " << line.substr(line.find(' ') + 1, -1) << std::endl;

                std::stringstream buffer(line.substr(line.find(' ') + 1, -1));  
                std::string word;

                while (buffer >> word) {
                    std::cout << "mot : " << word << std::endl;

                    list_files.push_back(word);

                    std::cout << list_files.size() << std::endl;
                }   
            }
            // -----------------------------------------------------

        }
    }
    // Checke si le fichier des intermediaires existe et le cree sinon
    if( !boost::filesystem::exists("intermediate/")){
        if(!boost::filesystem::create_directory("intermediate")){
            std::cout << "Fichier non créé" << std::endl;
            exit(1);
        }
    }

    // On crée ou récupére le fichier de cache
    std::fstream cacheFile("intermediate/.cache");
    cacheFile.close();
    




    // Compilation
    std::string str;
    const char *command;
    
    for (int i = 0; i < list_asso.size(); i++) {
        if(needCompiling(list_asso[i][1])){

            // Compilation des fichiers
            str = "g++ -c " + list_asso[i][1] + " -o intermediate/" + list_asso[i][0] + ".o";
            for (int i = 0; i < include_dir.size(); i++) {
                const char* envVar = std::getenv(include_dir[i].c_str());
                if(envVar != NULL){
                    std::string strEnvVar = envVar;
                    str += " -I"+strEnvVar;
                }
                else{
                    std::cerr << "Impossible de trouver la variable d'environement " + include_dir[i] << std::endl;
                    exit(1);
                }
            }

            command = str.c_str();

            std::cout << "ligne de commande : " << command << std::endl;
            system(command);
        }

    }
    
    // Compilation de l'executable
    str = "g++ ";
    for (int i = 0; i < list_files.size(); i++) {
        str += "intermediate/" + list_files[i] + ".o ";
    }
    for (int i = 0; i < library_dir.size(); i++) {
        const char* envVar = std::getenv(library_dir[i].c_str());
        if(envVar != NULL){
            std::string strEnvVar = envVar;
            str += " -L"+strEnvVar;
        }
        else{
            std::cerr << "Impossible de trouver la variable d'environement " + library_dir[i] << std::endl;
            exit(1);
        }
    }
    for (int i = 0; i < list_libs.size(); i++) {
        str += " -l" + list_libs[i].substr(3,-1) ;
    }

    str += " -o " + noun_exe;
    
    command = str.c_str();

    std::cout << "ligne de commande : " << command << std::endl;
    system(command);

    return true;
}





bool needCompiling(std::string filename){
    bool out = true;

    // On récup ce qu'il ya ds cache
    std::fstream cacheFile("intermediate/.cache");
    std::string cacheContent { 
        std::istreambuf_iterator<char>(cacheFile), std::istreambuf_iterator<char>() 
    };

    // On vérifie que le fichier est pas dans cache
    if(cacheContent.find(filename) != std::string::npos){
        // On récup le fichier 
        std::fstream file(filename);
        std::string fileContent { 
            std::istreambuf_iterator<char>(cacheFile), std::istreambuf_iterator<char>() 
        };

         
        // On vérifie que le hash a pas changé
        std::string line;
        std::string oldSHA;
        while(getline(cacheFile, line)){
            if(line.find(filename) != std::string::npos){
                oldSHA = line.substr(line.find(filename)+filename.length()+1,-1);
            }
        }

        if(calculateSHA(fileContent) == oldSHA){
            out = false;
        }
        else{
            // TODO: supprimer la ligne
        }


    }




    return out;
}




std::string calculateSHA(const std::string string){
    std::string SHAFinal = "";

    boost::uuids::detail::sha1 sha;
    sha.process_bytes(string.c_str(), string.length());

    unsigned int hash[5];
	sha.get_digest(hash);

	std::stringstream stream;
	for (int i = 0; i < 5; ++i) {
		stream << std::hex << hash[i];
	}
	SHAFinal =  stream.str();

    return SHAFinal;
}
