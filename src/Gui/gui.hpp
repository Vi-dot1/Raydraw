#pragma once

extern "C"{
    #include"raylib.h"
}


namespace Gui {

// Used to check whenever a point is inside the main panel area
bool IsOverPanel(const Vector2&);

// Draw/process call for the main panel
void drawGui1(); 

// Recalculates panels size when window is resized
void updatePanel();

}