#include "LineTool.hpp"

void LineTool::_drawToLayer(RenderTexture2D& target, const Vector2& pos)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool mHold = false;

    BeginTextureMode(target);

    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !mHold) 
    {
        mHold = true;
        lpos = pos;

        DrawCircle(pos.x, pos.y, this->brushSize, Brush::brushColor);
    }
    if( !IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mHold)
    {
        mHold = false;

        DrawLineEx(pos, lpos, Brush::brushSize*2, Brush::brushColor);
        DrawCircle(pos.x, pos.y, this->brushSize, Brush::brushColor);
    }

    EndTextureMode();

    if(mHold) DrawLineEx(pos, lpos, Brush::brushSize*2, Brush::brushColor);
}