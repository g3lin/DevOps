#include <iostream>

#include "utils.h"
#include "buildus.h"

int main(int argc, char *argv[]) {

    try {
        if(!getNbArgc(argc)) {
            
            std::cerr << "Le programme a besoin d'un unique argument" << std::endl;
            return(1); 
        }

        std::string argv1 = argv[1]; 

        if (argv1 == "clean")
        {
            cleanIntermediate();
            
            std::cout << "Dossier nettoyé" << std::endl;
            return(0); 
        }



        std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;


        if (argv1.substr(argv1.find('.'), -1) == ".buildus") {
            std::cout << "Extention de fichier OK" << std::endl;
        }

       
        
        if(checkArgv(argv1)) {
            getConfig(argv1);
            
        }
    }
    catch(const std::exception &ex)
    { 
        std::cerr << "Erreur" << std::endl;
        exit(1);

    }
    
    
    return 0;
}

