#include "commit.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/uuid/detail/sha1.hpp>


void getCommitHelp() {
    // Affichage du "./gitus commit --help"
    std::cout << "usage: gitus commit <msg> <author> <email>" << std::endl;
}

void setCommit(const char* message,const char* author,const char* email) throw(boost::filesystem::filesystem_error) {
    // Recuperer le chemin actuel
    auto path = boost::filesystem::current_path();

    // On va récupérer ce qui est en staging et en faire un arbre
    // On cherche donc ce qu'il y a dans le fichier index

    std::ifstream indexFile(".git/index");
	std::string indexContent { 
        std::istreambuf_iterator<char>(indexFile), std::istreambuf_iterator<char>() 
    };

    // On en fait un SHA
    std::string hashTree = calculateSHA(indexContent.c_str());
    //On crée l'arbre
     makeObject(hashTree,indexContent.c_str());

	std::ifstream headFile(".git/HEAD");
	std::string headContent { 
        std::istreambuf_iterator<char>(headFile), std::istreambuf_iterator<char>() 
    };




    // On va construire le hash du commit avec les infos suivantes :
    // tree [SHA1]
    // parent [SHA1]
    // author [author] <[email]> 
    // [MESSAGE]
    boost::uuids::detail::sha1 sha_commit;
    std::string hashParent= "00000000";

    
    std::stringstream commitContentS ;
    commitContentS << "tree " << hashTree << std::endl;
    if(headFile.good() && headContent != ""){
        commitContentS << "parent " << headContent << std::endl;
    }
    commitContentS << "author " << author << " <" << email << "> " << std::time(0) << std::endl;
    commitContentS << "committer " << author << " <" << email << "> " << std::time(0) << std::endl;
    commitContentS << message ;

    std::string commitContent = commitContentS.str();

	std::string SHACommit = calculateSHA(commitContent);
    makeObject(SHACommit, commitContent);

    indexFile.close();
    headFile.close();

    // Nettoyer et mettre à jour HEAD
    std::ofstream indexFileW;
    indexFileW.open(".git/index", std::ios::out | std::ios::trunc);
    indexFileW.close();

    std::ofstream headFileW;
    headFileW.open(".git/HEAD", std::ios::out | std::ios::trunc);
    headFileW<<SHACommit;
    headFileW.close();

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

