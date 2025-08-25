#pragma once

#include "tool.hpp"
extern "C"{
    #include "raylib.h"
}


class Brush : public Tool
{
public:
    void _drawToLayer(RenderTexture2D&, const Vector2&);
};
