#pragma once

#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>

// AB - argv1 c'est quoi?
// le nom du fichier?
// pouquoir ne pas l'appeler filePath?
bool getConfig(std::string argv1);
bool needCompiling(std::string filename);
std::string calculateSHA(const std::string string);