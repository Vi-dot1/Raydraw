#pragma once

#include "raylib.h"
#include "raymath.h"
#include "State/mouse.hpp"

inline bool isMouseOver(const Rectangle& space)
{
    return CheckCollisionPointRec(
        Mouse::getMouseState().pos, 
        space
    );
}

inline Vector2 translatePos(const Vector2& origin, const Vector2& pos)
{
    return Vector2Add(
        origin,
        pos
    );
}