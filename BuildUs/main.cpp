#include <iostream>

#include "argc.h"
#include "buildus.h"

int main(int argc, char *argv[]) {

    try {
        if(getNbArgc(argc)) {
            std::string argv1 = argv[1];
        }
        else{
            std::cerr << "Le programme a besoin d'un unique argument" << std::endl;
            exit(1);
        }
        std::string argv1 = argv[1];
        //std::cout << argv[1] << std::endl;

        if (argv1 == "clean")
        {
            // Code ci-dessous adapté de https://stackoverflow.com/questions/6935279/delete-all-txt-in-a-directory-with-c
            boost::filesystem::directory_iterator end;
            for(boost::filesystem::directory_iterator it("intermediate"); it != end; ++it)
            {
                try
                {
                    if(boost::filesystem::is_regular_file(it->status()) && (it->path().extension().compare(".o") == 0))
                    {
                        boost::filesystem::remove(it->path());
                    }
                }
                catch(const std::exception &ex)
                {
                    std::cerr << "Le nettoyage a échoué" << std::endl;
                    exit(1);

                }
            }
            std::cout << "Dossier nettoyé" << std::endl;
            exit(0);
        }



        std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;


        if (argv1.substr(argv1.find('.'), -1) == ".buildus") {
            std::cout << "Extention de fichier OK" << std::endl;
        }

        //std::cout << "Extention du fichier : " << argv1.substr(argv1.find('.'), -1) << std::endl;
        
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



