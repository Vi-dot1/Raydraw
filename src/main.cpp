extern "C"{
    #include"raylib.h"
}

#include "canvas.hpp"
#include "Brush/brush.hpp"
#include "Gui/gui.hpp"

constexpr int screenHeight = 600, screenWidth = 800;
constexpr Color mColor = DARKGRAY;

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Raydraw");
	HideCursor();
	SetTargetFPS(120);

	Brush b;
	Canvas canvas(screenWidth-196, screenHeight);

	Vector2 mpos;
	bool mouseAlreadyUsed = false;
	while(!WindowShouldClose())
	{
		mpos = GetMousePosition();

		BeginDrawing();
        ClearBackground(GRAY);

		// To avoid drawing on the canvas while clicking the controls
		if(mouseAlreadyUsed == false) b._drawToLayer(canvas.getCurrentLayer(), canvas.localCoord(mpos));
		mouseAlreadyUsed = drawGui();

		DrawCircleLinesV(mpos, Brush::brushSize, mColor);
		DrawCircleLinesV(mpos, 1, mColor);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
