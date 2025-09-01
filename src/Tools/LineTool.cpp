#include "canvas.hpp"
#include "mState.hpp"
#include "LineTool.hpp"
#include "raylib.h"
#include "tool.hpp"

void LineTool::_drawTo(Canvas& canvas)
{
    const Mouse::State& mState = Mouse::getMouseState();

    RenderTexture2D& target = canvas.getCurrentLayer();
    const Vector2& canvasPos = canvas.localCoord(mState.pos);

    BeginTextureMode(target);

    // Start point
    if( mState.IsHolding && !lineHold) 
    {
        lineHold = true;

        lastCanvasPos = canvasPos;
        lastPos = mState.pos;

        DrawCircle(canvasPos.x, canvasPos.y, Tool::size, Tool::color);
    }
    if( !mState.IsHolding && lineHold)
    {
        lineHold = false;

        DrawLineEx(canvasPos, lastCanvasPos, Tool::size*2, Tool::color);
        DrawCircle(canvasPos.x, canvasPos.y, this->size, Tool::color);
    }

    EndTextureMode();


    // Draw a line showing how the line would look once drawn
    if(lineHold) DrawLineEx(mState.pos, lastPos, Tool::size*2*canvas.canvasView.zoom, Tool::color);
}