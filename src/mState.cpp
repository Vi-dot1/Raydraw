#include"raylib.h"
#include"mState.hpp"


namespace Mouse
{

// vvv This is the object the state of the mouse is written into (Am I writing too many comments?)
static State mouseState;

const State& getMouseState()
{
    return mouseState;
}

void updateState()
{
    mouseState.pos = GetMousePosition();

    mouseState.wasHolding = mouseState.IsHolding;
    mouseState.IsHolding = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // To check if we consumed an input click, we check if we complete
    mouseState.inputConsumed = mouseState.wasHolding && !mouseState.IsHolding;
}

const ProgramState& getProgramState()
{
    return mouseState.state;
}
void setProgramState(ProgramState&& state)
{
    mouseState.state = state;
}

void markUsed()
{
    mouseState.inputConsumed = true;
}
bool wasAlreadyUsed()
{
    return mouseState.inputConsumed;
}

const Vector2& getPos()
{
    return mouseState.pos;
}

// I'll maybe use them later?
void setPos(const Vector2& pos)
{
    mouseState.pos = pos;
}

}

