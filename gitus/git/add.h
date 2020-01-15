#pragma once

#include <boost/filesystem.hpp>

void getAddHelp();
void setAddFile(const char* file_to_add) throw(boost::filesystem::filesystem_error);