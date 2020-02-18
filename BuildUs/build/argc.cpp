#include "argc.h"

#include <iostream>

bool getNbArgc(int argc) {
    // Verifier le nombre d'arguments passes
    if(argc < 2) {
        std::cerr << "ERREUR : Aucun argument place en parametre" << std::endl;

        return false;
    
    }
    
    if(argc > 2) {
        std::cerr << "ERREUR : Trop d'arguments places en parametre" << std::endl;

        return false;

    }
    
    if(argc == 2) {
        return true;

    }
}

bool checkArgv(std::string argv1) {
    // Verifier l'extention du fichier
    if(argv1.substr(argv1.find('.'), -1) == ".buildus") {
        return true;
    
    }else {
        std::cerr << "ERREUR : Mauvaise extention de fichier" << std::endl;

        return false;

    }
}

