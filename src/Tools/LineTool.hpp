#pragma once

#include "canvas.hpp"
#include "tool.hpp"

class LineTool : public Tool
{
    Vector2 lastCanvasPos = (Vector2){-1, -1};
    Vector2 lastPos = (Vector2){-1, -1};

    // True wehn we clicked the first point of a line
    bool lineHold = false;

public:
    void _drawTo(Canvas& target);
};