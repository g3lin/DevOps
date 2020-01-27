#pragma once

#include <boost/filesystem.hpp>

bool getCommitHelp();
bool setCommit(const char* message,const char* author,const char* email) throw(boost::filesystem::filesystem_error);
std::string parseLine(std::string TreeHash, std::string index);