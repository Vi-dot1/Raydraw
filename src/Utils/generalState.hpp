#pragma once

/*
 * Some files in a project can be considered as the glue,
 * the ugly part that is there to make components actually work
 * with each other.
 *
 * 
*/

#include "Tools/tool.hpp"
#include "canvas.hpp"

namespace Program {

enum class State {DEFAULT};

struct pState
{
    State state = State::DEFAULT;
};

const pState& getProgramState();
const State& getState();

const Tool* getCurrentTool();
void setCurrentTool(Tool* t);

Canvas* getCurrentCanvas();
void setCurrentCanvas(Canvas* c);

}