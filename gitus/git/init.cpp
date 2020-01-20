#include "init.h"

#include <iostream>
#include <fstream>

void getInitHelp() {
    // Affichage du "./gitus init --help"
    std::cout << "usage: gitus init" << std::endl;
}

void setInit() throw(boost::filesystem::filesystem_error) {
    // Recuperer le chemin actuel
    auto path = boost::filesystem::current_path();

    // Creer le dossier '.gitus'
    const auto pathFolderGitus = path.append(".git");
    boost::filesystem::create_directory(pathFolderGitus);

    // Creer le fichier 'index'
    boost::filesystem::ofstream index(".git/index");
    index.close();

    // Creer le dossier 'objects'
    const auto pathFolderObjects = path.append("objects");
    boost::filesystem::create_directory(pathFolderObjects);
}
