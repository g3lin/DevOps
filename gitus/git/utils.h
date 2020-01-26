#pragma once

#include <boost/filesystem.hpp>

void makeObject(const std::string SHA, const std::string content);
std::string calculateSHA(const std::string string);