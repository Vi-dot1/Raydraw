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

    static bool mHold = false;

    BeginTextureMode(target);

    // Start point
    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !mHold) 
    {
        mHold = true;
        lastCanvasPos = canvasPos;
        lastPos = mState.pos;

        DrawCircle(canvasPos.x, canvasPos.y, Tool::size, Tool::color);
    }
    if( !IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mHold)
    {
        mHold = false;

        DrawLineEx(canvasPos, lastCanvasPos, Tool::size*2, Tool::color);
        DrawCircle(canvasPos.x, canvasPos.y, this->size, Tool::color);
    }

    EndTextureMode();


    if(mHold) DrawLineEx(mState.pos, lastPos, Tool::size*2*canvas.canvasView.zoom, Tool::color);
}