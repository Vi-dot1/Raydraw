#include "raylib.h"

#include "Utils/mState.hpp"

#include "canvas.hpp"
#include "LineTool.hpp"
#include "tool.hpp"

void LineTool::_drawTo(Canvas& canvas)
{
    const Mouse::mState& state = Mouse::getMouseState();

    RenderTexture2D& target = canvas.getCurrentLayer();
    const Vector2& canvasPos = canvas.localCoord(state.pos);

    BeginTextureMode(target);

    // Start point
    if( state.IsHolding && !lineHold) 
    {
        lineHold = true;

        lastCanvasPos = canvasPos;
        lastPos = state.pos;

        DrawCircle(canvasPos.x, canvasPos.y, Tool::size, Tool::color);
    }
    if( !state.IsHolding && lineHold)
    {
        lineHold = false;

        DrawLineEx(canvasPos, lastCanvasPos, Tool::size*2, Tool::color);
        DrawCircle(canvasPos.x, canvasPos.y, this->size, Tool::color);
    }

    EndTextureMode();

    // Draw a line showing how the line would look once drawn
    if(lineHold) DrawLineEx(state.pos, lastPos, Tool::size*2*canvas.canvasView.zoom, Tool::color);
}