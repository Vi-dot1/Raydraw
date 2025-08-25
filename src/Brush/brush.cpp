#include"brush.hpp"

void Brush::_drawToLayer(RenderTexture2D& target, const Vector2&canvasOffset)
{
    static Vector2 lpos = (Vector2){-1, -1};
    static bool stillDrawing = false;

	BeginTextureMode(target);

    if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) 
    {
        DrawCircle(canvasOffset.x,canvasOffset.y, Tool::size, Tool::color);
    }
    if( stillDrawing ) 
    {
        DrawLineEx(canvasOffset, lpos, Tool::size*2, Tool::color);
    }
    
    EndTextureMode();

    lpos = canvasOffset;
    stillDrawing = IsMouseButtonDown( MOUSE_BUTTON_LEFT );
}