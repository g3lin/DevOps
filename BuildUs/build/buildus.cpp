
#include <fstream>
#include <iostream>
#include "buildus.h"
#include <sstream>
#include <string>
#include <vector>
#include "utils.h"

std::string deleteSpaces(std::string line) {
    // Eviter les problemes d'espaces oublies
    if(line.find(" ") != std::string::npos) {
        std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());

    }

    return line;
}

bool getConfig(std::string configFileName) {
    // Recuperer le chemin actuel
	const auto path = boost::filesystem::current_path();

	// Lire le fichier 'index'
	std::ifstream config(configFileName); 

    // Variables de stockage
    std::string appName; 

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
                std::cout << "nom de l'executable : " << line.substr(line.find(':') + 1, -1) << std::endl;
                
                appName = deleteSpaces(line.substr(line.find(':') + 1, -1).c_str());

            }
            // -----------------------------------------------------
            // Recuperer les libraires -----------------------------
            if(isLibrary) {
                if(line.find("var") != std::string::npos) {
                    library_dir.push_back(deleteSpaces(line.substr(line.find(' ') + 1, -1)));

                }else {
                    isLibrary = false;
                }
            }

            if(line.find("deps_library") != std::string::npos) {
                isLibrary = true;
            }
            // -----------------------------------------------------

            // Recuperer les includes ------------------------------
            if(isInclude) {
                if(line.find("var") != std::string::npos) {
                    include_dir.push_back(line.substr(line.find(' ') + 1, -1));
                    std::cout<< "include: "+line.substr(line.find(' ') + 1, -1)<<std::endl;
     
                }else {
                    isInclude = false;
                }
                
            }

            if(line.find("deps_include") != std::string::npos) {
                isInclude = true;
            }
            // -----------------------------------------------------

            if(isLibs) {
                if(line.find("-") != std::string::npos) {
                    list_libs.push_back(deleteSpaces(line.substr(line.find('-') + 1, -1)));

                }else {
                    isLibs = false;
                }
            }

            if(line.find("libs") != std::string::npos) {
                isLibs = true;
            }
            // -----------------------------------------------------

            // Recuperer l'association entre variable et fichier ---
            if(isCompile){
                if(line.find("-") != std::string::npos) {
                    association[0] = deleteSpaces(line.substr(line.find('-') + 1, line.find(':') - 1));
                    association[1] = deleteSpaces(line.substr(line.find(':') + 1, -1));
                    
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

                    list_files.push_back(deleteSpaces(word));

                    std::cout << list_files.size() << std::endl;
                }   
            }
            // -----------------------------------------------------

        }
    }


    // Checke si le fichier des intermediaires existe et le cree sinon
    if( !checkIfFileExists("intermediate/")){
        if(!boost::filesystem::create_directory("intermediate")){
            std::cout << "Fichier non créé" << std::endl;
            exit(1);
        }
    }


    // Necessaire pour créer le fichier si besoin
    std::fstream cacheFile;  
    cacheFile.open("intermediate/.cache",std::ios::in | std::ios::out);
    cacheFile.close();

    // Compilation
    std::string commandStr; 
    
    for (int i = 0; i < list_asso.size(); i++) {
        if(needCompiling(list_asso[i][1])){
            // On calcule le SHA du fichier à ajouter
            std::fstream fileToAdd(list_asso[i][1]);
            std::string fileContent { 
                std::istreambuf_iterator<char>(fileToAdd), std::istreambuf_iterator<char>() 
            };

            std::fstream cacheFile("intermediate/.cache",std::ios::app);
            cacheFile << list_asso[i][1] + " " + calculateSHA(fileContent) << std::endl;
            cacheFile.close();

            // Compilation des fichiers
            commandStr = "g++ -c " + list_asso[i][1] + " -o intermediate/" + list_asso[i][0] + ".o";
            for (int i = 0; i < include_dir.size(); i++) {
                const char* envVar = std::getenv(include_dir[i].c_str());
                if(envVar != NULL){
                    std::string strEnvVar = envVar;
                    commandStr += " -I"+strEnvVar;
                }
                else{
                    std::cerr << "Impossible de trouver la variable d'environement " + include_dir[i] << std::endl;
                    exit(1);
                }
            }

            std::cout << "ligne de commande : " << commandStr.c_str() << std::endl;
            if(system(commandStr.c_str()) != 0){
                std::cerr << "LA compilation a rencontée un problème " << std::endl;
                exit(1);

            }
        }

    }
    
    // Compilation de l'executable
    commandStr = "g++ ";
    for (int i = 0; i < list_files.size(); i++) {
        commandStr += "intermediate/" + list_files[i] + ".o ";
    }
    for (int i = 0; i < library_dir.size(); i++) {
        const char* envVar = std::getenv(library_dir[i].c_str());
        if(envVar != NULL){
            std::string strEnvVar = envVar;
            commandStr += " -L"+strEnvVar;
        }
        else{
            std::cerr << "Impossible de trouver la variable d'environement " + library_dir[i] << std::endl;
            exit(1);
        }
    }
    for (int i = 0; i < list_libs.size(); i++) {
        commandStr += " -l" + list_libs[i].substr(3,-1) ;
    }

    commandStr += " -o " + appName;
    

    std::cout << "ligne de commande : " << commandStr.c_str() << std::endl;
    if (system(commandStr.c_str())!= 0){
        std::cerr << "LA compilation a rencontée un problème " << std::endl;
        exit(1);

    }

    return true;

}





bool needCompiling(std::string filenameToCompile){
    bool valReturn = true; 

    // On récup ce qu'il ya ds cache
    std::fstream cacheFile;
    cacheFile.open("intermediate/.cache",std::ios::in | std::ios::out);

    // On récup le fichier 
    std::fstream file(filenameToCompile); 
    std::string fileContent { 
        std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() 
    };

        
    // On vérifie que le hash a pas changé
    std::string line; 
    std::string oldSHA;
    std::string updatedCache = "";
    while(getline(cacheFile, line)){
        if(line.find(filenameToCompile) != std::string::npos){
            oldSHA = line.substr(line.find(filenameToCompile)+filenameToCompile.length()+1,-1);
            if(calculateSHA(fileContent) == oldSHA){
                std::cout << "Le fichier " << filenameToCompile << " est dejà compilé, ignoré" << std::endl;
                valReturn = false;
                updatedCache += line+"\n";
            }
            else{
                std::cout << "Le fichier " << filenameToCompile << " a été modifié. Recompilation ..." << std::endl;

            }

        }
        else{
                updatedCache += line+"\n";
        }
    }
            

    cacheFile.close();

    cacheFile.open("intermediate/.cache", std::ios::out);
    cacheFile << updatedCache;
    cacheFile.close();

    return valReturn;
}





