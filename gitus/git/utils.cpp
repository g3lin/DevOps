#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/uuid/detail/sha1.hpp>

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

void makeObject(const std::string SHA, const std::string content){
    auto path = boost::filesystem::current_path();

    // Creer le dossier 'content.substr(0, 2)'
    const auto pathFolderContent = path.append(".git/objects/" + SHA.substr(0, 2));
    boost::filesystem::create_directory(pathFolderContent);

	// Creer le fichier 'content' et le remplit
	std::ofstream sha_content(path.append(SHA.substr(2,-1)).c_str());
    sha_content.seekp(0) << content;
    sha_content.close();

}