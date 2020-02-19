#include "utils.h"
#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <sstream>

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

    // Autres cas
    return false;
}

bool checkArgv(std::string argv1) {
    // Verifier l'extention du fichier
    if(argv1.substr(argv1.find('.'), -1) == ".buildus") {
        return true;
    
    }else {
        std::cerr << "ERREUR : Mauvaise extension de fichier" << std::endl;

        return false;

    }
}

bool checkIfFileExists(std::string filename){
    try{
        return boost::filesystem::exists(filename);
    }
    catch(const boost::filesystem::filesystem_error& e)
    {
        std::cerr << "Erreur" << std::endl;
        exit(1);
    }    
}

bool cleanIntermediate(){

    try{
        boost::filesystem::directory_iterator end;
                for(boost::filesystem::directory_iterator it("intermediate"); it != end; ++it)
                {
                    if(boost::filesystem::is_regular_file(it->status()) && ((it->path().extension().compare(".o") == 0) || (it->path().extension().compare(".cache") == 0)))
                    {
                        boost::filesystem::remove(it->path());
                    }
                }
    }
    catch(const boost::filesystem::filesystem_error& e)
    {
        std::cerr << "Le nettoyage a échoué" << std::endl;
        return 1;
    }

    return 0;
}




std::string calculateSHA(const std::string string){
    std::string SHAFinal = "";

    boost::uuids::detail::sha1 sha;
    sha.process_bytes(string.c_str(), string.length());

    unsigned int hash[5];
	sha.get_digest(hash);

	std::stringstream stream;
	for (int i = 0; i < 5; ++i) {
		stream << std::hex << hash[i];
	}
	SHAFinal =  stream.str();

    return SHAFinal;
}

std::string getCacheSHA(){
    std::fstream cache("intermediate/.cache");
	std::string cacheContent { 
		std::istreambuf_iterator<char>(cache), std::istreambuf_iterator<char>() 
	};
	return calculateSHA(cacheContent);
}

