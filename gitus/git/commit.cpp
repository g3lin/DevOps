#include "commit.h"
#include "utils.h"

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

    std::ifstream headFile(".git/HEAD");
	std::string headContent { 
        std::istreambuf_iterator<char>(headFile), std::istreambuf_iterator<char>() 
    };

    std::string previousTreeHash  = "";
    if(headFile.good() && headContent != ""){
        // On cherche l'arbre précédent
        std::ifstream previousCommitFile(".git/objects/"+headContent.substr(0, 2)+ "/" + headContent.substr(2,-1));
        std::string previousCommitContent { 
            std::istreambuf_iterator<char>(previousCommitFile), std::istreambuf_iterator<char>() 
        };
        
        previousTreeHash  = previousCommitContent.substr(5,previousCommitContent.find("\n")-5);        
    }

    


    // On va récupérer ce qui est en staging et en faire un arbre
    // On cherche donc ce qu'il y a dans le fichier index
    std::ifstream indexFile(".git/index");
	std::string indexContent { 
        std::istreambuf_iterator<char>(indexFile), std::istreambuf_iterator<char>() 
    };


    // On va parser l'index pour chaque ligne
    std::string indexContentLine = "";
    while(indexContent.find("\n") != -1){
        // On isole une ligne
        indexContentLine = indexContent.substr(0,indexContent.find("\n"));
        indexContent = indexContent.substr(indexContent.find("\n")+1, -1);

        // On gere la ligne
        previousTreeHash = parseLine(previousTreeHash, indexContentLine);

    }
    std::string hashTree = parseLine(previousTreeHash, indexContentLine);

    // On recupere le SHA





    // On va construire le hash du commit avec les infos suivantes :
    // tree [SHA1]
    // parent [SHA1]
    // author [author] <[email]> 
    // [MESSAGE]

    
    std::stringstream commitContentS ;
    commitContentS << "tree " << hashTree << std::endl;
    if(headFile.good() && headContent != ""){
        commitContentS << "parent " << headContent << std::endl;
    }
    commitContentS << "author " << author << " <" << email << "> " << std::time(0) << std::endl;
    commitContentS << "committer " << author << " <" << email << "> " << std::time(0) << std::endl << std::endl;
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


std::string parseLine(std::string TreeHash, std::string index){
    
    std::string SHAReturn = "";
    std::string TreeContent = ""  ;
    // std::cout << TreeHash << std::endl ;

    // On va ouvrir l'arbre pour en avoir le contenu ssi on a un hash
    if (TreeHash != ""){
        std::ifstream TreeFile(".git/objects/"+TreeHash.substr(0, 2)+ "/" + TreeHash.substr(2,-1));
        std::string TreeContent_temp { 
            std::istreambuf_iterator<char>(TreeFile), std::istreambuf_iterator<char>() 
        };
        TreeContent = TreeContent_temp;
        std::cout << TreeContent << std::endl ;
    }
 
    

    // On cherche le nom et le hash du fichier à ajouter
    std::string SHA = index.substr(0,index.find(" "));
    std::string pathname = index.substr(index.find(" ")+1,-1);


    if (pathname.find("/") == -1){
        // Ce n'est pas un dossier juste un fichier

        // On vérifie si ce fichier n'est pas dans TreeContent
        if( TreeContent.find(pathname) != -1){
            TreeContent.replace(TreeContent.find(pathname)-41 , TreeContent.find(pathname)+pathname.length()+6 , "");
        }
        TreeContent += SHA + " " + pathname + " blob\n"; 
        SHAReturn = calculateSHA(TreeContent);
        makeObject(SHAReturn, TreeContent);
    }

    else{
        // On est dans un dossier, il faut faire de la recursivité
        std::string folder = pathname.substr(0,pathname.find("/"));
        std::string subPathName = pathname.substr(pathname.find("/")+1,-1); 
        
        std::string SHASubTree = "";
        // On checke si le sous dossier existe deja
        if( TreeContent.find(folder) != -1){
            std::cout << "222222222222222"<<pathname<<folder<<subPathName << std::endl;
            SHASubTree = TreeContent.substr(TreeContent.find(folder)-41, 40);
            TreeContent.replace(TreeContent.find(folder)-41 , TreeContent.find(folder)+folder.length()+6, "");
        }

        std::string SHASubReturn = parseLine(SHASubTree, SHA + " " + subPathName);
        TreeContent += "\n" + SHASubReturn + " " + folder + " tree\n"; 
        SHAReturn = calculateSHA(TreeContent);
        makeObject(SHAReturn, TreeContent);

    }

    
    return SHAReturn;
}




