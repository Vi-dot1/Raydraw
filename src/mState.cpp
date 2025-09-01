#include"raylib.h"
#include"mState.hpp"


namespace Mouse
{

//
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

// I'll maybe use them later?
const Vector2& getPos()
{
    return mouseState.pos;
}
void setPos(const Vector2& pos)
{
    mouseState.pos = pos;
}

}

