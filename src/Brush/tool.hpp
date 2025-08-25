#pragma once

extern "C"{
    #include "raylib.h"
}

// A general interface that everything that want to draw into a canvas must use
class Tool
{
public:
    inline static float size = 3;
    inline static Color color = BLACK;

    // Thus the name
    virtual void _drawToLayer(RenderTexture2D&, const Vector2&);
};
