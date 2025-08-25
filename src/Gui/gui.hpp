#pragma once

#include<functional>
extern "C"{
    #include"raylib.h"
}

#include"Brush/tool.hpp"

namespace Gui {

bool IsOverPanel(const Vector2&);

// Draw call point for main, returns whenever or not the mouse was used
bool drawGui(); 

// Recalculates panels size when window is resized
void updatePanel();

}