#pragma once

#include<cstddef>
#include <memory>
#include <vector>

extern "C"{
    #include "raylib.h"
}
#define MAX_LAYERS 80

/*
Struct used to compact `Canvas` data to be saved
*/
struct CanvasData
{
    int width;
    int height;
    Camera2D canvasView;


    size_t layerAmount;
    std::vector<int> bytesPerlayer;

    // All the layers are packed into a byte array
    // which will be read to get each layer back
    std::unique_ptr<unsigned char[]> data;
};

/* 
Used to create and represent canvas objects.

Features:
- Canvas are formed by an array of `RenderTexture2D`, allowing multiple layers 
- Canvas are rendered using a `Camera2D` space defined in `canvasView`, allowing to change the angle the canvas is seen
*/
class Canvas
{
    RenderTexture2D layers[MAX_LAYERS];
    size_t currenLayer=0, layerAmount=1;

    // Canvas position in window
    Vector2 cPos = (Vector2){0, 0};
    int width, height;
    bool changed = false;

public:
    Camera2D canvasView;

    Canvas(int width, int height);
    Canvas(CanvasData& c);
    ~Canvas();

    // Returns `RenderTexture2D` of the currently selected layer
    RenderTexture2D& getCurrentLayer();

    void changeLayer(size_t);
    void addLayer();

    void _draw();

    /*
    Returns an `Image` of the canvas by overlapping all the layers top to bottom
    The canvas will only give out the image, saving it as a file is not its responsability
    */
    Image _exportImage();

    /*
    Returns all the relevant data as a `CanvasData` object
    */
    void _getData(CanvasData &c);

    /*
    Turns Screen coordinates to canvas coordinates, 
    mostly used to get the coordinates where something should to be drawn
    */
    inline Vector2 localCoord(const Vector2 &coord) 
    { 
        // This raylib function gets the Camera Matrix and multiplies coord by it
        return GetScreenToWorld2D(coord, canvasView);
    };
};
