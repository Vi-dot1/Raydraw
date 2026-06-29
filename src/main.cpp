extern "C"{
    #include "raylib.h"
}
#include "raymath.h"


#include "canvas.hpp"
#include "Gui/gui.hpp"

#include "Tools/brush.hpp"

#include "Utils/mouseState.hpp"
#include "Utils/generalState.hpp"

constexpr int screenHeight = 600, screenWidth = 800;

int main(int argc, char** argv)
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow(screenWidth, screenHeight, "Raydraw");
	HideCursor();
	SetTargetFPS(120);

	// Initialize Panel Size
	Gui::updatePanel();

	// Background is literally just an Image generated using raylibs default gen algorithms
	Texture2D editorBackground = LoadTextureFromImage(
		GenImageChecked(
			GetScreenWidth(), GetScreenWidth(), 
			6, 6, GRAY, DARKGRAY
		)
	);

	Brush b;
	Canvas canvas(screenWidth, screenHeight);
    
    Program::setCurrentCanvas(&canvas);

	Vector2 mpos;
	while(!WindowShouldClose())
	{
		Mouse::updateState();
		mpos = Mouse::getPos();

		if( IsWindowResized() )
		{
			Gui::updatePanel();
			editorBackground = LoadTextureFromImage(
				GenImageChecked(
					GetScreenWidth(), GetScreenWidth(), 
					6, 6, GRAY, DARKGRAY
				)
			);
		}
        
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
			Program::getCurrentCanvas()->canvasView.zoom += GetMouseWheelMove()*0.05;

			// TO avoid drawing while dragging 
			Mouse::markUsed();
		}
        
        // Redering
		BeginDrawing();
		DrawTexture(editorBackground, 0, 0, RAYWHITE);

        if( Program::getCurrentCanvas() ) 
        {
            Program::getCurrentCanvas()->_draw();
        }

		Gui::draw();
		if( !Mouse::wasAlreadyUsed() ) b._drawTo(canvas);
		EndDrawing();
	}

	CloseWindow();
	UnloadTexture(editorBackground);
	return 0;
}
