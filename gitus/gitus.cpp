#include <iostream>

#include <dummy.h>
#include <init.h>
#include <add.h>

int main(int argc, char *argv[]) {
    
	//TestDeTrucs();
    //std::cout << GetAnswerToLifeUniverseAndEverything() << std::endl;

    //std::cout << argv[1] << std::endl;
    //std::cout << argv[2] << std::endl;
    std::string argv1 = "";
    std::string argv2 = "";

    if(argv[1]) {
        argv1 = argv[1];
    }
    if(argv[2]) {
        argv2 = argv[2];
    }

    if(argv1 == "init") {
        // Fonctions du fichier "init.cpp"
        if(argv2 == "--help") {
            getInitHelp();
        }else {
            setInit();
        }    
    }

    if(argv1 == "add") {
        // Fonctions du fichiers "add.cpp"
        if(argv2 == "--help") {
            getAddHelp();
        }else {
            setAddFile(argv2.c_str());
        }
        
    }

    return 0;
}



