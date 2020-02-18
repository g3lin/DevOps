#include "argc.h"

#include <iostream>

bool getNbArgc(int argc) {
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

