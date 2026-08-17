#include "State/mouse.hpp"
#include "./canvas.hpp"

#include "./tool.hpp"
#include "./brush.hpp"

void Brush::_drawTo(Canvas& canvas)
{
    const Mouse::mState& mouse = Mouse::getState();

    RenderTexture2D& target = canvas.getCurrentLayer();
    Vector2 pos = canvas.localCoord(mouse.pos);

	BeginTextureMode(target);
        if( stillDrawing ) 
        {
            DrawLineEx(pos, lastPos, Tool::size*2, Tool::color);
        }
        stillDrawing = false;

        if( mouse.state == Mouse::State::CLICK || mouse.state == Mouse::State::HOLD ) 
        {
            DrawCircle(pos.x, pos.y, Tool::size, Tool::color);
            stillDrawing = true;
        }
    
    EndTextureMode();
    lastPos = pos;
}