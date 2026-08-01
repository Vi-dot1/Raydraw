#pragma once

#include "Utils/mouseState.hpp"
#include "raymath.h"
extern "C"{
    #include"raylib.h"
}

namespace Gui {

struct Component {
    float x, y, w, h;

    virtual void draw();
};

struct Panel {
    Rectangle space;
    float marging=0.f;
    bool visible=true;

    // Translates a position with the Panel top-right corner as its origin
    Vector2 translatePos(const Vector2& pos) {
        return Vector2Add(Vector2(space.x, space.y), pos);
    }
    bool isMouseOver() {
        return CheckCollisionPointRec(Mouse::getMouseState().pos, space);
    }
};

// Draw/process call for the main panel
void draw(); 

// Recalculates panels size when window is resized
// Used to check whenever a point is inside the main panel area
bool IsMouseOverPanel();
void updatePanel();

}