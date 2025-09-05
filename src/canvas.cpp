#include "canvas.hpp"
#include "raylib.h"
#include <assert.h>
#include <vector>

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

Canvas::Canvas(CanvasData& c)
{
    // Load the easy stuff first
    width = c.width;
    height = c.height;
    canvasView = c.canvasView;

    layerAmount = c.layerAmount;
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
void Canvas::_getData(CanvasData &c)
{

    // Simple cofig data
    c.width = width;
    c.height = height;
    c.canvasView = canvasView;

    // Layer data and format
    c.layerAmount = layerAmount;

    c.bytesPerlayer = std::vector<int>(layerAmount);

    int ImageByteSize = GetPixelDataSize(width, height, layers[currenLayer].texture.format);

    // Make space in the data buffer for the image data
    c.data.reset(new unsigned char[ImageByteSize*layerAmount]);

    // Get into loading
    for(int layerIdx=0, dataIdx=0; layerIdx<layerAmount; ++layerIdx)
    {
        static Image img;

        // First we loaded as the later an Image to move the data into ram
        img = LoadImageFromTexture(layers[layerIdx].texture);

        // Compress the img data using into a png
        int size;
        unsigned char *layerBuffer = ExportImageToMemory(img, ".png", &size);

        // Save the amount of bytes in the layer
        c.bytesPerlayer[layerIdx] = size;

        /* 
        Write it in the data byte array,

        Pay attention to the fact that the loop also increases dataIdx, 
        all the layers are concadenated on the same buffer
        
        Done this since the main purpose of `CanvasData` is to be written into a binary file to save the canvas state
        */
        for(int i=0; i<size; ++i, ++dataIdx)
        {
            c.data.get()[dataIdx] = layerBuffer[i];
        }

        // Unload the layer image, free the layerBuffer data, rinse and repeat
        UnloadImage(img);
        MemFree(layerBuffer);
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