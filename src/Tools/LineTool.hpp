#pragma once

#include "canvas.hpp"
#include "tool.hpp"

class LineTool : public Tool
{
    Vector2 lastCanvasPos = (Vector2){-1, -1};
    Vector2 lastPos = (Vector2){-1, -1};

public:
    void _drawTo(Canvas& target);
};