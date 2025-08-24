#include"brush.hpp"

float Brush::brushSize = 3;
Color Brush::brushColor = BLACK;

void Brush::_drawToLayer(RenderTexture2D& target, const Vector2&canvasOffset)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool stillDrawing = false;

	BeginTextureMode(target);
    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) 
    {
        DrawCircle(canvasOffset.x,canvasOffset.y, this->brushSize, brushColor);
    }
    if( stillDrawing ) 
    {
        DrawLineEx(canvasOffset, lpos, this->brushSize*2, brushColor);
    }
    EndTextureMode();

    lpos =canvasOffset;
    stillDrawing = IsMouseButtonDown( MOUSE_BUTTON_LEFT );
}