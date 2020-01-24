#pragma once

#include <boost/filesystem.hpp>

void getCommitHelp();
void setCommit(const char* message,const char* author,const char* email) throw(boost::filesystem::filesystem_error);
void makeObject(const std::string SHA, const std::string content);
std::string calculateSHA(const std::string string);