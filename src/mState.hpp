#pragma once

#include "raylib.h"
enum class mStates { draw, hold, normal };


namespace Mouse
{

const mStates& getState();
void setState(mStates&& state);

void setPos(const Vector2& pos);
const Vector2& getPos();

}