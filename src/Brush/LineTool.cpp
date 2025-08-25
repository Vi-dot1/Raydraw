#include "LineTool.hpp"
#include "tool.hpp"

void LineTool::_drawToLayer(RenderTexture2D& target, const Vector2& pos)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool mHold = false;

    BeginTextureMode(target);

    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !mHold) 
    {
        mHold = true;
        lpos = pos;

        DrawCircle(pos.x, pos.y, Tool::size, Tool::color);
    }
    if( !IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mHold)
    {
        mHold = false;

        DrawLineEx(pos, lpos, Tool::size*2, Tool::color);
        DrawCircle(pos.x, pos.y, this->size, Tool::color);
    }

    EndTextureMode();

    if(mHold) DrawLineEx(pos, lpos, Tool::size*2, Tool::color);
}