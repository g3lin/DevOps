#pragma once

#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>

bool getConfig(std::string argv1);
bool needCompiling(std::string filename);
std::string calculateSHA(const std::string string);