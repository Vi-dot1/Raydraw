#pragma once

#include "brush.hpp"

class LineTool : public Brush
{
public:
    void _drawToLayer(RenderTexture2D& target, const Vector2& pos);
};