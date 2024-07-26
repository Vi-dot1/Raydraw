#include"brush.h"

int Brush::brushSize = 3;
Color Brush::brushColor = BLACK;

void Brush::_drawToLayer(RenderTexture2D& target, Vector2& pos)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool stillDrawing = false;

	BeginTextureMode(target);

    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) DrawCircle(pos.x, pos.y, this->brushSize, brushColor);
    if( stillDrawing ) DrawLineEx(pos, lpos, this->brushSize*2, brushColor);

    EndTextureMode();

    lpos = pos;
    stillDrawing = IsMouseButtonDown( MOUSE_BUTTON_LEFT );
}