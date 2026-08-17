#pragma once

#include <string>

namespace File {
enum class popUp {INFO, QUESTION, ERROR, WARNING};

/*
Opens a window that halts execution and allows the user to select a file
once a file is selected a path to it is returned

`ext` receives a list of file entensions in a string separated by semicolons

*eg. `"one;two;three"` -> file.one, file.two or file.three*
*/
std::string openFileSelect(const std::string& ext="", bool save=false);

std::string openFolderSelect();

bool popUpConfirm(const std::string& tittle, const std::string& msg, const popUp& type);
void popUpInfo(const std::string&,const std::string&, const popUp& type);

}