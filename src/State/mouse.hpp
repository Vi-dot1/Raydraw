#pragma once

#include "raylib.h"


namespace Mouse
{

enum class State { CLICK, HOLD, NORMAL };

/*
    Struct used to hold mouses state
*/
struct mState
{
    State state = State::NORMAL;

    Vector2 pos = Vector2(0, 0);
    Vector2 lastPos = Vector2(0, 0);
    Vector2 delta = Vector2(0, 0);
    
    bool inputConsumed=false;
};

/*
    Returns a constant reference to the used `Mouse::State` object containing relevant mouse data.
*/
const mState& getState();

/*
    Fetches and saves current mouse position along with the current input state,
    also an enum `ProgramState` representing the current program state of the mouse.

    Must be called at the start of each frame.
*/
void updateState();
const Vector2& getPos();

/*
    Updates the `inputConsumed` field on the `Mouse::State` object, 
    used to tell any other component processed after that it cannot use the mouse.
*/
void markUsed();
}