#include "buildus.h"

#include <fstream>
#include <iostream>
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

    std::vector<std::string> association(2);
    std::vector< std::vector<std::string> > list_asso;

    std::vector<std::string> list_files;

    if(config) {
        std::string line;
        bool isCompile = false;

        while(getline(config, line)){
            //std::cout << "ligne : " << line << std::endl;

            // Recuperer le nom de l'executable
            if(line.find("projet") != std::string::npos) {
                std::cout << "nom de l'executable : " << line.substr(line.find(' ') + 1, -1) << std::endl;
                
                noun_exe = line.substr(line.find(' ') + 1, -1).c_str();
            }

            // Recuperer l'association entre variable et fichier
            if(isCompile){
                if(line.find("-") != std::string::npos) {

                    association[0] = line.substr(line.find('-') + 1, line.find(':') - 1);
                    association[1] = line.substr(line.find(':') + 1, -1);
                    
                    std::cout << "liste : " << association[0] << " >> " << association[1] << std::endl;

                    list_asso.push_back(association);
                
                }else {
                    isCompile = false;
                }
            }

            if(line.find("compile") != std::string::npos) {
                isCompile = true;
            }

            // Recuperer les fichiers a utiliser
            if(line.find("package") != std::string::npos) {
                std::cout << "fichiers utilises : " << line.substr(line.find(' ') + 1, -1) << std::endl;

                //list_files.push_back(line.substr(line.find(' ') + 1, line.find(' ') - 1));
            }
        }
    }

    return true;
}