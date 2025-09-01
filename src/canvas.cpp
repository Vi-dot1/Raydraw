#include "canvas.hpp"
#include "raylib.h"

Canvas::Canvas(int _width, int _height)
    : width(_width), height(_height)
{
    layers[0] = LoadRenderTexture(width, height);


    // You have to define all values
    // for the camera to work

    // Position the camera a lil' bit to the left so the drawin and the panel down overlap that much
    float camHOffset = -40;

    canvasView.target = {(float)width/2+camHOffset, (float)height/2};
    canvasView.offset = {(float)width/2, (float)height/2};
    canvasView.rotation = 0;
    canvasView.zoom = 0.8;

    // Filling first layer
    BeginTextureMode(layers[0]);
    ClearBackground(RAYWHITE);
    EndTextureMode();
}

Image Canvas::_exportImage()
{
    RenderTexture2D r = LoadRenderTexture(layers[0].texture.width, layers[0].texture.height);


    BeginTextureMode(r);
    this->_draw();
    EndTextureMode();
    
    return LoadImageFromTexture(r.texture);
}

Canvas::~Canvas()
{
    for(size_t i=0; i<layerAmount; ++i)
    {
	    UnloadRenderTexture(layers[i]);
    }
}

RenderTexture2D& Canvas::getCurrentLayer()
{
    return layers[currenLayer];
}

void Canvas::_draw()
{
    //if(!changed) return;

    BeginMode2D(canvasView);

    float outLineThickness=2;
    DrawRectangleLinesEx(
        (Rectangle)
        {
            -outLineThickness, -outLineThickness, 
            (float)layers[0].texture.width+outLineThickness*2, 
            (float)layers[0].texture.height+outLineThickness*2
        }, 

        outLineThickness, BLACK
    );

    for(size_t i=0; i<layerAmount; ++i)
    {
		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(
            layers[i].texture, 
            (Rectangle)
                {
                    0,0, 
                    (float)layers[0].texture.width, 
                    (float)-layers[0].texture.height 
                }, 

            (Vector2){0, 0}, 
            WHITE
        );
    }

    EndMode2D();
}