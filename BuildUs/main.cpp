#include <iostream>

#include "buildus.h"

int main(int argc, char *argv[]) {

    try {
        std::string argv1 = argv[1];
        //std::cout << argv[1] << std::endl;

        std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;

        if (argv1.substr(argv1.find('.'), -1) == ".buildus") {
            std::cout << "Extention de fichier OK" << std::endl;

            getConfig(argv1);
        
        }else {
            std::cerr << "ERREUR : Mauvaise extention de fichier" << std::endl;

        }
        

        //return true;

    }catch(std::string const& chaine) {
        std::cerr << chaine << std::endl;

        //return false;
    
    }
    
    return 0;
}



