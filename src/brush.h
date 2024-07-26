#pragma once

extern "C"{
    #include "raylib.h"
}

class Brush
{
public:
    static int brushSize;
    static Color brushColor;
    virtual void _drawToLayer(RenderTexture2D&, Vector2&);
};
