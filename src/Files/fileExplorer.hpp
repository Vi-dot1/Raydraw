#pragma once

#include <vector>
#include <string>

namespace File {
enum class popUp {INFO, QUESTION, ERROR, WARNING};

/*
Opens a window that halts execution and allows the user to select a file
once a file is selected a path to it is returned
*/
std::string openFileSelect(const std::string& tittle, const std::vector<const char*>& ext, bool save);
std::string openFolderSelect();

bool popUpConfirm(const std::string& tittle, const std::string& msg, const popUp& type);
void popUpInfo(const std::string&,const std::string&, const popUp& type);

}