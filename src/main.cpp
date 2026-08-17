#include "Gui/comps.hpp"
#include "Gui/gui.hpp"
#include "Tools/tool.hpp"
extern "C"{
    #include "raylib.h"
}
#include "raymath.h"

#include "Tools/brush.hpp"

#include "State/mouse.hpp"
#include "State/general.hpp"

#include "Tools/canvas.hpp"
#include "Files/canvas.hpp"

int main(int argc, char** argv)
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow(Program::getState().windowSize.x, Program::getState().windowSize.y, "Raydraw");
	SetTargetFPS(60);

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
    Program::setCurrentCanvas(&canvas);

    Texture2D img = LoadTextureFromImage(
        GenImageCellular(100, 100, 9)
    );
    Gui::ImageButton imgB;
    imgB.src = img;
    
    Gui::Panel panel;
    panel.updateRect({10, 10, 150, 150});
    Gui::ColorPicker c;
    panel.appendComp(&c);

    
	while( !WindowShouldClose() )
	{
        Program::updateState();
		Mouse::updateState();
        
        auto& general = Program::getState();
        auto& mouse = Mouse::getState();

		if( general.resized )
		{
            // Update background 
			editorBackground = LoadTextureFromImage(
				GenImageChecked(
					GetScreenWidth(), GetScreenWidth(), 
					6, 6, GRAY, DARKGRAY
				)
			);
		}

        Tool::color = c.color;

		if(  IsKeyDown(KEY_LEFT_CONTROL) and Program::getCurrentCanvas() )
		{
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
        
        if( IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S) )
        {
            Files::saveCanvasAsPng("image.png", *Program::getCurrentCanvas());
        }
        
        bool canDraw = !(mouse.inputConsumed || CheckCollisionPointRec(mouse.pos, panel.bounds));
		if( canDraw ) 
        {
            b._drawTo(canvas);
        }
        // Redering
		BeginDrawing();
		DrawTexture(editorBackground, 0, 0, RAYWHITE);

        if( Program::getCurrentCanvas() ) 
        {
            Program::getCurrentCanvas()->_draw();
        }
        panel.draw();

		EndDrawing();
	} // Main loop end

    auto cData = canvas._getData();

	CloseWindow();
	UnloadTexture(editorBackground);
    UnloadTexture(img);
	return 0;
}
