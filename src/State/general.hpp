#pragma once

/*
 * Some files in a project can be considered as the glue,
 * the ugly part that is there to make components actually work
 * with each other.
 *
 * 
*/

#include "Tools/tool.hpp"
#include "Tools/canvas.hpp"
#include "raylib.h"

namespace Program {

enum class State {DEFAULT};
constexpr int defScreenHeight = 600, defScreenWidth = 800;

struct pState
{
    Vector2 windowSize = Vector2{defScreenWidth, defScreenHeight};
    bool resized=false;
};
void updateState();

const pState& getState();

const Tool* getCurrentTool();
void setCurrentTool(Tool* t);

Canvas* getCurrentCanvas();
void setCurrentCanvas(Canvas* c);

}