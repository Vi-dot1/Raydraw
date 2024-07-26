#pragma once

#include "brush.h"

class LineTool : public Brush
{
public:
    void _drawToLayer(RenderTexture2D& target, Vector2& pos, Color c);
};