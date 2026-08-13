#pragma once

#include <string>
#include "Tools/canvas.hpp"

namespace Files
{

void saveCanvasAsPng(const std::string path, Canvas& c);

void saveAsRdraw(const std::string pathStr, CanvasData& cData);
CanvasData loadRdrawFile(const std::string pathStr);

}