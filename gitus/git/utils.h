#pragma once

#include <boost/filesystem.hpp>

void makeObject(const std::string SHA, const std::string content);
std::string calculateSHA(const std::string string);
std::string readFile(const std::string filename);
void writeFile(const std::string filename, const std::string data);
