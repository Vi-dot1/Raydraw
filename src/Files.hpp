#pragma once

#include <string>
#include "canvas.hpp"

namespace Files
{

void saveCanvasAsPng(const std::string path, Canvas& c);
void saveCanvasAsRdraw(const std::string path, Canvas& c);

}