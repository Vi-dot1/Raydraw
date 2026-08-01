#include"State/mouse.hpp"
#include"canvas.hpp"

#include"tool.hpp"
#include"brush.hpp"

void Brush::_drawTo(Canvas& canvas)
{
    const Mouse::mState& state = Mouse::getMouseState();

    RenderTexture2D& target = canvas.getCurrentLayer();
    Vector2 pos = canvas.localCoord(state.pos);

	BeginTextureMode(target);

        if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) 
        {
            DrawCircle(pos.x, pos.y, Tool::size, Tool::color);
        }
        if( stillDrawing ) 
        {
            DrawLineEx(pos, lastPos, Tool::size*2, Tool::color);
        }
    
    EndTextureMode();

    lastPos = pos;
    stillDrawing = IsMouseButtonDown( MOUSE_BUTTON_LEFT );
}