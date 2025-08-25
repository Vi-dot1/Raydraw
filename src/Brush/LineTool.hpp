#pragma once

#include "tool.hpp"

class LineTool : public Tool
{
public:
    void _drawToLayer(RenderTexture2D& target, const Vector2& pos);
};