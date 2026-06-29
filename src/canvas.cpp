#include "canvas.hpp"
#include "raylib.h"
#include <assert.h>
#include <vector>

Canvas::Canvas(int _width, int _height)
    : width(_width), height(_height)
{
    layers[0] = LoadRenderTexture(width, height);


    // Position the camera a lil' bit to the left so the canvas and the panel don't overlap that much
    float camHOffset = -40;

    canvasView.target = {(float)width/2+camHOffset, (float)height/2};
    canvasView.offset = {(float)width/2, (float)height/2};
    canvasView.rotation = 0;
    canvasView.zoom = 0.8;

    // First layer
    BeginTextureMode(layers[0]);
    ClearBackground(RAYWHITE);
    EndTextureMode();
}

Canvas::Canvas(CanvasData& c) :
    width(c.props.width), height(c.props.height), 
    canvasView(c.props.canvasView), layerAmount(c.layerAmount)
{
}

Image Canvas::_exportImage()
{
    RenderTexture2D r = LoadRenderTexture(layers[0].texture.width, layers[0].texture.height);

    // temporarily saving canvasView
    Camera2D temp = canvasView;

    /*
    Exporting the canvas is just drawing it onto a texture

    Since `_draw()` uses canvasView to draw the canvas,
    so we need to fix its position and zoom to export it properly
    */
    {
        canvasView.zoom = 1.0;
        canvasView.offset = canvasView.target = (Vector2){0, 0};
    }

    BeginTextureMode(r);
    this->_draw();
    EndTextureMode();
    
    // Loading back the current canvas view settings
    canvasView = temp;

    return LoadImageFromTexture(r.texture);
}

// TODO: test if this thing would even work
CanvasData Canvas::_getData()
{ 
    CanvasData c;

    c.props.width = width;
    c.props.height = height;
    c.props.canvasView = canvasView;
    c.layerAmount = layerAmount;

    c.bytesPerlayer.reserve(layerAmount);
    c.layerData.reserve(layerAmount);

    // Get into loading
    for(int layerIdx=0; layerIdx<layerAmount; ++layerIdx)
    {
        // First we loaded as an Image to move the data from gpu to ram
        Image img;
        img = LoadImageFromTexture(layers[layerIdx].texture);
        
        // then we get the raw data of that image, this fuction will also give us its size
        int size;
        c.layerData.emplace_back(ExportImageToMemory(img, ".bmp", &size));

        // Save the amount of bytes in the layer
        c.bytesPerlayer[layerIdx] = size;

        UnloadImage(img);
    }
    return c;
}

void Canvas::_setData(const CanvasData &c)
{
    width = c.props.width;
    height = c.props.height;
    canvasView = c.props.canvasView;
    layerAmount = c.layerAmount;

    for(int layerIdx=0; layerIdx<layerAmount; ++layerIdx)
    {
        // We need to turn the image into a texture in order to draw it
        Image img = LoadImageFromMemory(".bmp", c.layerData[layerIdx], c.bytesPerlayer[layerIdx]);
        Texture tex = LoadTextureFromImage(img);

        // Redo the layer
        UnloadRenderTexture(layers[layerIdx]);
        layers[layerIdx] = LoadRenderTexture(width, height);
        
        // ANd then we basically have to draw the layer into the texture
        BeginTextureMode(layers[layerIdx]);
            DrawTexture(tex, 0, 0, RAYWHITE);
        EndTextureMode();
        
        UnloadImage(img);
        UnloadTexture(tex);
    }
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
    return layers[currenLayerIdx];
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