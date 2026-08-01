#include "Utils/generalState.hpp"
#include "Tools/tool.hpp"
#include "canvas.hpp"


namespace Program 
{

static pState programState;

const pState& getState() 
{
    return programState;
}

static Tool* _currTool = nullptr;
const Tool* getCurrentTool()
{
    return  _currTool;
}
void setCurrentTool(Tool* t)
{
    _currTool = t;
}

static Canvas* _currCanvas = nullptr;
Canvas* getCurrentCanvas()
{
    return _currCanvas;
}
void setCurrentCanvas(Canvas* c)
{
    _currCanvas = c;
}

}
