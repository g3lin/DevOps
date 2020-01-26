#pragma once

#include <boost/filesystem.hpp>

bool checkInit();
bool getInitHelp();
bool setInit() throw(boost::filesystem::filesystem_error);
