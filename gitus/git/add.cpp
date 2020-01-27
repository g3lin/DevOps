#include "add.h"
#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/uuid/detail/sha1.hpp>

bool checkAdd() {
	// Recuperer le chemin actuel
	auto path = boost::filesystem::current_path();

	// Lire le fichier 'index'
	std::ifstream index(".git/index");

	if(index) {
		std::string line;

		while(getline(index, line)) {
			//std::cout << "ligne : " << line << std::endl;

			std::string sha = line.substr(0, line.find(' '));
			//std::cout << "sha : " << sha << std::endl;

			if(!boost::filesystem::exists(".git/objects/" + sha.substr(0, 2)) || !boost::filesystem::exists(".git/objects/" + sha.substr(0, 2) + "/" + sha.substr(2, -1))){
				return false;
			}
		}

		return true;

	}else {
		std::cerr << "ERREUR : Impossible d'ouvrir le fichier en lecture." << std::endl;

		return false;

	}
	
}

bool getAddHelp() {
    // Affichage du "./gitus add --help"

	try {
    	std::cout << "usage: gitus add <pathspec>" << std::endl;

		return true;
	
	} catch(std::string const& chaine) {
        std::cerr << chaine << std::endl;

        return false;
    
    }
}

bool setAddFile(const char* file_to_add) throw(boost::filesystem::filesystem_error) {
	try {
		// Recuperer le chemin actuel
		auto path = boost::filesystem::current_path();

		if(boost::filesystem::exists(".git")) {
			
			std::ifstream file(file_to_add);
			std::string content { 
				std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() 
			};

			// Creation d'un sha
			boost::uuids::detail::sha1 sha;
			sha.process_bytes(content.c_str(), content.length());

			unsigned int hash[5];
			sha.get_digest(hash);

			std::stringstream stream;

			std::string result;
			for (int i = 0; i < 5; ++i) {
				stream << std::hex << hash[i];
			}
			content += stream.str();

			// Creer le dossier 'content.substr(0, 2)'
			const auto pathFolderContent = path.append(".git/objects/" + stream.str().substr(0, 2));
			boost::filesystem::create_directory(pathFolderContent);

			// Creer le fichier 'content'
			std::ofstream sha_content(path.append(stream.str().substr(2,-1)).c_str());
			sha_content.close();

			writeFile(".git/objects/" + stream.str().substr(0, 2)+"/"+stream.str().substr(2,-1), content);
			

			// Ajoute le sha et le fichier a l'index
			std::fstream index(".git/index");

			if (index) {
				std::stringstream oss;
				oss << stream.str() << " " << file_to_add << "\n" << index.rdbuf();
				index.seekp(0) << oss.str();

			}else {
				std::cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << std::endl;
			}

			index.close();

			//std::cout << content << std::endl;

			return true;
		
		}else {
			std::cerr << "ERREUR : Aucun répertoire '.git' trouvé." << std::endl;

			return false;

		}
		
	} catch(std::string const& chaine) {
        std::cerr << chaine << std::endl;

        return false;
    
    }

}