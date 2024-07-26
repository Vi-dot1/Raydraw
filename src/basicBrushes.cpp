#include "basicBrushes.h"

void LineTool::_drawToLayer(RenderTexture2D& target, Vector2& pos, Color c)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool mHold = false;

    BeginTextureMode(target);

    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !mHold) 
    {
        mHold = true;
        lpos = pos;

        DrawCircle(pos.x, pos.y, this->brushSize, BLACK);
    }
    if( !IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mHold)
    {
        mHold = false;

        DrawLineEx(pos, lpos, Brush::brushSize*2, c);
        DrawCircle(pos.x, pos.y, this->brushSize, BLACK);
    }

    EndTextureMode();

    if(mHold) DrawLineEx(pos, lpos, Brush::brushSize*2, c);
}