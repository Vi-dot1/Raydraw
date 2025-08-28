#include <string>
extern "C"{
    #include"raylib.h"
}
#include"raymath.h"

#include "canvas.hpp"
#include "Brush/brush.hpp"
#include "Gui/gui.hpp"

constexpr int screenHeight = 600, screenWidth = 800;
constexpr Color mColor = DARKGRAY;

enum class mStates { draw, hold, normal };
mStates mState = mStates::draw;

int main(int argc, char** argv)
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow(screenWidth, screenHeight, "Raydraw");
	HideCursor();
	SetTargetFPS(120);

	// Initialize Panel Size
	Gui::updatePanel();

	Brush b;
	Canvas canvas(screenWidth, screenHeight);

	Vector2 mpos;
	while(!WindowShouldClose())
	{
		bool mouseAlreadyUsed = false;
		mpos = GetMousePosition();


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
			mouseAlreadyUsed = true;

			mState = mStates::hold;
		}
		else
		{
			mState = mStates::draw;
		}

		BeginDrawing();
        ClearBackground(GRAY);


		canvas._draw();

		// To avoid drawing on the canvas while clicking on the controls
		mouseAlreadyUsed |= Gui::drawGui(mpos);

		if(mouseAlreadyUsed == false) b._drawToLayer(canvas.getCurrentLayer(), canvas.localCoord(mpos));

		DrawText(
			("mpos: [" + std::to_string(mpos.x) + ", " + std::to_string(mpos.x) + "]").c_str(), 
			GetScreenWidth()-180, 0, 
			12, BLACK
		);
		
		// Mouse
		switch(mState)
		{
			case mStates::draw:
			DrawCircleLinesV(mpos, Tool::size*canvas.canvasView.zoom, mColor);
			DrawCircleLinesV(mpos, 1, mColor);
			break;

			case mStates::hold:
			DrawCircleV(mpos, Tool::size*canvas.canvasView.zoom, mColor);
			break;

			default:
			break;
		};

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
