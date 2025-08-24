#pragma once

extern "C"{
    #include "raylib.h"
}

class Brush
{
public:
    static float brushSize;
    static Color brushColor;
    virtual void _drawToLayer(RenderTexture2D&, const Vector2&);
};
