#pragma once

#include <boost/filesystem.hpp>

void getCommitHelp();
void setCommit(const char* message,const char* author,const char* email) throw(boost::filesystem::filesystem_error);
std::string parseLine(std::string TreeHash, std::string index);