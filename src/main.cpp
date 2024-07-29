extern "C"{
    #include"raylib.h"
}

#include "basicBrushes.h"
#include "canvas.h"
#include "gui.h"

int screenHeight = 600, screenWidth = 800;

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Raydraw");
	HideCursor();
	SetTargetFPS(120);

	Brush b;
	Canvas canvas(screenWidth-196, screenHeight);

	Vector2 mpos;
	while(!WindowShouldClose())
	{
		mpos = GetMousePosition();

		// Save Canvas as png
		if( IsKeyPressed(KEY_S) )
		{
			Image image = canvas._exportImage();
            ImageFlipVertical(&image);
            ExportImage(image, "draw.png");
            UnloadImage(image);
		}

		// Drawing to window
		BeginDrawing();
        ClearBackground((Color){120, 120, 120, 255});

		canvas._draw(196, 0); // show canvas
		b._drawToLayer(canvas.getCurrentLayer(), canvas.localCoord(mpos));

		drawGui();
		DrawCircleLinesV(mpos, Brush::brushSize, Brush::brushColor);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
