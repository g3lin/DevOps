#pragma once

#include <boost/filesystem.hpp>

void getInitHelp();
void setInit() throw(boost::filesystem::filesystem_error);
