#include "fileExplorer.hpp"

#include "tinyfiledialogs.hpp"
#include <string>
#include <utility>

namespace File {

const char* getTypeStr(const popUp& type)
{
    switch(type)
    {
        case popUp::INFO:
            return "info";
        break;
        case popUp::QUESTION:
            return "question";
        break;
        case popUp::WARNING:
            return "warning";
        break;
        case popUp::ERROR:
            return "error";
        break;
    }
    return "";
}

std::string openFileSelect(const std::string& ext, bool save)
{
    std::string path;
    
    if( save )
    {
    }
    
    return std::move(path);
}

bool popUpConfirm(const std::string& tittle, const std::string& msg, const popUp& type)
{
    return tinyfd_messageBox(
        tittle.c_str(), msg.c_str(), 
        "yesno", 
        getTypeStr(type), 
        0
    );
}

void popUpInfo(const std::string& tittle, const std::string& msg, const popUp& type)
{
    tinyfd_messageBox(
        tittle.c_str(), msg.c_str(), 
        "ok", 
        getTypeStr(type), 
        0
    );
}

}