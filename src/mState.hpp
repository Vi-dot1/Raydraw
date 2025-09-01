#pragma once

#include "raylib.h"


namespace Mouse
{

enum class ProgramState { draw, hold, normal };

/*
Struct used to hold mouses state, not intended to be created directly.

A reference to the current mouse state can be obtained using the `getMouseState()` function.
*/
struct State
{
    ProgramState state = ProgramState::draw;

    Vector2 pos;
    bool inputConsumed = false;

    bool IsHolding = false;
    bool wasHolding = false;
};

/*
Returns a constant reference to the used `Mouse::State` object containing relevant mouse data.

Modifying the state of the mouse must be done using the provided set functions.
*/
const State& getMouseState();

/*
Fetches and saves current mouse position along with the current input state,
also an enum `ProgramState` representing the current program state of the mouse.

Must be called on the main at the start of each frame.
*/
void updateState();

const ProgramState& getProgramState();
void setProgramState(ProgramState&& state);

const Vector2& getPos();
}