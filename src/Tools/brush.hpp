#pragma once

#include "tool.hpp"

class Brush : public Tool
{
    Vector2 lastPos = (Vector2){-1, -1};
    bool stillDrawing = false;

public:
    void _drawTo(Canvas&);
};
