#pragma once

extern "C"{
    #include"raylib.h"
}

#include"Tools/tool.hpp"

namespace Gui {

bool IsOverPanel(const Vector2&);

// Draw call point for main, returns whenever or not the mouse was used
bool drawGui(const Vector2 &mpos); 

// Recalculates panels size when window is resized
void updatePanel();

}