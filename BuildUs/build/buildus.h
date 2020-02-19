#pragma once
#include <boost/filesystem.hpp>


// AB - argv1 c'est quoi?
// le nom du fichier?
// pouquoir ne pas l'appeler filePath?
bool getConfig(std::string argv1);
bool needCompiling(std::string filename);
std::string calculateSHA(const std::string string);