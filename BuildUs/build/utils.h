#pragma once

#include <boost/filesystem.hpp>

// AB - les noms des parametres ne sont pas supers
bool getNbArgc(int argc);
bool checkArgv(std::string argv1);
bool checkIfFileExists(std::string filename);
bool cleanIntermediate();
std::string calculateSHA(const std::string string);
std::string getCacheSHA();