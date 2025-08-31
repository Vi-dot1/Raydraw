#include"raylib.h"
#include"mState.hpp"

static struct State
{
    mStates state = mStates::draw;

    Vector2 pos;
    bool hold = false;
    bool inputConsumed = false;
}
mouseState;

namespace Mouse
{

/*
Fetches and saves mouse position along with current input state 
and an enum representing the current program state of the mouse.

Must be called on the main at the start of each frame.
*/
void updateState()
{

    mouseState.pos = GetMousePosition();

    // To check if consumed the input
    mouseState.inputConsumed = mouseState.hold;

    mouseState.hold = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

const mStates& getState()
{
    return mouseState.state;
}

void setState(mStates&& state)
{
    mouseState.state = state;
}

const Vector2& getPos()
{
    return mouseState.pos;
}

void setPos(const Vector2& pos)
{
    mouseState.pos = pos;
}

}

