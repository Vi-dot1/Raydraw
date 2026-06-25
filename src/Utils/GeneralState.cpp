#include "Utils/GeneralState.hpp"
#include "Tools/tool.hpp"
#include "canvas.hpp"


namespace Program 
{

static pState programState;

const pState& getProgramState() 
{
    return programState;
}
const State& getState() 
{
    return programState.state;
}

}
