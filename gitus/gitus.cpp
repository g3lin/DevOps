#include <iostream>

#include <init.h>
#include <add.h>
#include <commit.h>

int main(int argc, char *argv[]) {
    
	//TestDeTrucs();
    //std::cout << GetAnswerToLifeUniverseAndEverything() << std::endl;

    //std::cout << argv[1] << std::endl;
    //std::cout << argv[2] << std::endl;
    std::string argv1 = "";
    std::string argv2 = "";
    std::string argv3 = "";
    std::string argv4 = "";

    if(argv[1]) {
        argv1 = argv[1];
    }
    if(argv[2]) {
        argv2 = argv[2];
    }
    if(argv[3]) {
        argv3 = argv[3];
    }
    if(argv[4]) {
        argv4 = argv[4];
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

    if(argv1 == "commit") {
        // Fonctions du fichiers "commit.cpp"
        if(argv2 == "--help") {
            getCommitHelp();
        }else {
            setCommit(argv2.c_str(), argv3.c_str(), argv4.c_str());
        }
        
    }

    return 0;
}



