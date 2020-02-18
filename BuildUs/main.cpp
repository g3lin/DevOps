#include <iostream>

#include "argc.h"
#include "buildus.h"

int main(int argc, char *argv[]) {
    if(getNbArgc(argc)) {
        std::string argv1 = argv[1];

        //std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;
        
        if(argv1.substr(argv1.find('.'), -1) == ".buildus") {
            getConfig(argv1);
        
        }else {
            std::cerr << "ERREUR : Mauvaise extention de fichier" << std::endl;

        }
    }
    
    return 0;
}



