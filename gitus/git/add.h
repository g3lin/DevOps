#pragma once

#include <boost/filesystem.hpp>

bool checkAdd();
bool getAddHelp();
bool setAddFile(const char* file_to_add) throw(boost::filesystem::filesystem_error);