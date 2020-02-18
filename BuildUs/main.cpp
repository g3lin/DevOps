#include <iostream>

#include "argc.h"
#include "buildus.h"

int main(int argc, char *argv[]) {
    if(getNbArgc(argc)) {
        std::string argv1 = argv[1];

        //std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;
        
        if(checkArgv(argv1)) {
            getConfig(argv1);
            
        }
    }
    
    return 0;
}



