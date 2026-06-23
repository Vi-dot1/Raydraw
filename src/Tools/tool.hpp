#pragma once

extern "C"{
    #include "raylib.h"
}
#include "canvas.hpp"

// A general interface that everything that want to draw into a canvas must use
class Tool
{
public:
// Inline is what allows me to define these static vars inside the declaration
// I'm writing this bc I keep checkin this feel, and forgeting why is inline -_-
    inline static float size = 3;
    inline static Color color = BLACK;

    // Thus the name
    virtual void _drawTo(Canvas&) = 0;


private:
    static Tool* currentTool;
public:
    static Tool* getCurrent() { return currentTool; }

    static void setCurrent(Tool* t)
    {
        if( t == nullptr || typeid(*t) == typeid(Tool) )
        {
            return;
        }
        currentTool = t;
    }
};