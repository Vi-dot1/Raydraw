#include"State/mouse.hpp"
#include"canvas.hpp"

#include"tool.hpp"
#include"brush.hpp"

void Brush::_drawTo(Canvas& canvas)
{
    const Mouse::mState& mouse = Mouse::getState();

    RenderTexture2D& target = canvas.getCurrentLayer();
    Vector2 pos = canvas.localCoord(mouse.pos);

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
    stillDrawing = (mouse.state == Mouse::State::HOLD);
}