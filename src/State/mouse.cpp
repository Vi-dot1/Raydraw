#include"raylib.h"
#include"State/mouse.hpp"


namespace Mouse
{

// vvv This is the object the state of the mouse is written into (Am I writing too many comments?)
static mState mouseState;

const mState& getState()
{
    return mouseState;
}

void updateState()
{
    mouseState.inputConsumed = false;
    mouseState.lastPos = mouseState.pos;
    mouseState.pos = GetMousePosition();
    mouseState.delta = GetMouseDelta();

    if( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
    {
        if( mouseState.state == State::CLICK )
        {
            mouseState.state = State::HOLD;
        }
        else
        {
            mouseState.state = State::CLICK;
        }
    }
    else mouseState.state = State::NORMAL;
}

void setState(State&& state)
{
    mouseState.state = state;
}
void markUsed()
{
    mouseState.inputConsumed = true;
}
const Vector2& getPos()
{
    return mouseState.pos;
}
}

