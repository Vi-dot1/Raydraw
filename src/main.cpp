#include "Gui/gui.hpp"
#include <iostream>
extern "C"{
    #include "raylib.h"
}
#include "raymath.h"

#include "Tools/brush.hpp"

#include "State/mouse.hpp"
#include "State/general.hpp"

#include "Gui/comps.hpp"

#include "canvas.hpp"
#include "files.hpp"

int main(int argc, char** argv)
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow(Program::getState().windowSize.x, Program::getState().windowSize.y, "Raydraw");
	//HideCursor();
	SetTargetFPS(120);

	// Background is literally just an Image generated using raylibs default gen algorithms
	Texture2D editorBackground = LoadTextureFromImage(
		GenImageChecked(
			GetScreenWidth(), GetScreenWidth(), 
			6, 6, GRAY, DARKGRAY
		)
	);
    
    // Temp
	Brush b;
	Canvas canvas(Program::getState().windowSize);
 
    // Ok so I need cData to get dropped so I'll just make another scope
    {
        CanvasData cData = Files::loadRdrawFile("file.rdraw");
        if( !cData.isNull() ) {
            std::cout<<"File loaded"<<std::endl;
            canvas._setData(cData);
        }
    }
    Program::setCurrentCanvas(&canvas);

	Vector2 mpos;
	while( !WindowShouldClose() )
	{
		Mouse::updateState();
		mpos = Mouse::getPos();

        Mouse::setState(Mouse::State::draw);
		if(  IsKeyDown(KEY_LEFT_CONTROL) and Program::getCurrentCanvas() )
		{
			Mouse::setState(Mouse::State::hold);

            // Handle Dragging
			if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) )
            {
				Program::getCurrentCanvas()->canvasView.target = Vector2Subtract(canvas.canvasView.target, GetMouseDelta());
            }

            // Handle Zoom
            float zoom = (
             GetMouseWheelMove()*0.05 +
             Program::getCurrentCanvas()->canvasView.zoom
            );
            if( zoom >= 0 ) Program::getCurrentCanvas()->canvasView.zoom = zoom;

			// TO avoid drawing while dragging 
			Mouse::markUsed();
		}
        
        if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_S))
        {
            Files::saveCanvasAsPng("image.png", *Program::getCurrentCanvas());
            std::cout<<"Image saved!"<<std::endl;
        }
        
        // Redering
		BeginDrawing();
		DrawTexture(editorBackground, 0, 0, RAYWHITE);

        if( Program::getCurrentCanvas() ) 
        {
            Program::getCurrentCanvas()->_draw();
        }

		if( !Mouse::wasAlreadyUsed() ) b._drawTo(canvas);
		EndDrawing();
	} // Main loop end

    auto cData = canvas._getData();
    Files::saveAsRdraw("file.rdraw", cData);

	CloseWindow();
	UnloadTexture(editorBackground);
	return 0;
}
