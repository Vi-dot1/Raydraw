#pragma once

#include "Utils/mouseState.hpp"
#include "raymath.h"
extern "C"{
    #include"raylib.h"
}

namespace Gui {

struct Component {
    float left, right, up, down;
    Rectangle bounds = {0,0,0,0};
    virtual void draw() = 0;

    // Calculate space inside panel using anchors
    // called automatically for `panel`
    void updateRect(Rectangle& panelSpace) {
        bounds.x = (panelSpace.width*left) + panelSpace.x;
        bounds.width = (panelSpace.width*right) + panelSpace.x;
        bounds.y = (panelSpace.height*up) + panelSpace.y;
        bounds.height = (panelSpace.height*down) + panelSpace.y;
    }
};

class Panel {
    Rectangle space;
    float marging=0.f;

public:
    bool visible=true;
    void appendComp(const Component& comp);

    // Draw/process call for the main panel
    void draw(); 
    // Recalculates panels size when window is resized
    // Used to check whenever a point is inside the main panel area
    bool IsMouseOver();
    void updatePanel();

    // Translates a position with the Panel top-right corner as its origin
    Vector2 translatePos(const Vector2& pos) {
        return Vector2Add(
            Vector2(space.x, space.y), 
            pos
        );
    }
    bool isMouseOver() {
        return CheckCollisionPointRec(
            Mouse::getMouseState().pos, 
            space
        );
    }
};


}