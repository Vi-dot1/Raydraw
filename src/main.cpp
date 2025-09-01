#include "Tools/LineTool.hpp"
#include <iostream>
#include <string>
extern "C"{
    #include"raylib.h"
}
#include"raymath.h"

#include "canvas.hpp"
#include "Tools/brush.hpp"
#include "Gui/gui.hpp"

#include"mState.hpp"

constexpr int screenHeight = 600, screenWidth = 800;
constexpr Color mColor = DARKGRAY;


int main(int argc, char** argv)
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow(screenWidth, screenHeight, "Raydraw");
	HideCursor();
	SetTargetFPS(120);

	// Initialize Panel Size
	Gui::updatePanel();

	LineTool b;
	Canvas canvas(screenWidth, screenHeight);

	Vector2 mpos;
	while(!WindowShouldClose())
	{
		Mouse::updateState();

		mpos = Mouse::getPos();


		if( IsWindowResized() )
		{
			Gui::updatePanel();
		}

		if(  IsKeyDown(KEY_LEFT_CONTROL) )
		{
			if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) )
				canvas.canvasView.target = Vector2Subtract(canvas.canvasView.target, GetMouseDelta());

			canvas.canvasView.zoom += GetMouseWheelMove()*0.05;

			// TO avoid drawing while dragging the screen
			Mouse::markUsed();

			Mouse::setProgramState(Mouse::ProgramState::hold);
		}
		else
		{
			Mouse::setProgramState(Mouse::ProgramState::draw);
		}

		BeginDrawing();
        ClearBackground(GRAY);


		// Show canvas on the screen
		// Drawing is up to the brush
		canvas._draw();


		Gui::drawGui1();

		if( !Mouse::wasAlreadyUsed() ) b._drawTo(canvas);

		
		// What the mouse looks like in each state
		switch( Mouse::getProgramState() )
		{
			case Mouse::ProgramState::draw:
			DrawCircleLinesV(mpos, Tool::size*canvas.canvasView.zoom, mColor);
			DrawCircleLinesV(mpos, 1, mColor);
			break;

			case Mouse::ProgramState::hold:
			DrawCircleV(mpos, Tool::size*canvas.canvasView.zoom, mColor);
			break;

			default:
			DrawCircleV(mpos, Tool::size*canvas.canvasView.zoom, mColor);
			break;
		};

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
