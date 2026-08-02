#pragma once

#include <vector>

extern "C"{
    #include "raylib.h"
}
constexpr size_t MAX_LAYERS = 80;

/*
Struct used to compact `Canvas` data to be saved
*/

struct CanvasProperties
{
    int width = 0;
    int height = 0;
    int format = 0;
    Camera2D canvasView;
};

struct CanvasData
{
    CanvasProperties props = {0, 0, 0, {0, 0, 0, 0}};
    size_t layerAmount = 0; // Needed when saved into a file

    // Layer size is only affected by dimensions and imae format, 
    // each layer has the same size
    size_t layerSize = 0; 
    std::vector<Image> layerData;
    
    // Just in case...
    ~CanvasData()
    {
        for( auto layer : layerData )
        {
            UnloadImage(layer);
        }
    }
    
    CanvasData(){}

    CanvasData(const CanvasData&cData)
    {
        this->layerData = cData.layerData;
        this->layerAmount = cData.layerAmount;
        this->layerSize = cData.layerSize;
        this->props = cData.props;
    }
    CanvasData(CanvasData &&cData)
    {
        this->layerData = std::move(cData.layerData);
        // To avoid the destructor from unloading the images
        cData.layerData.clear();

        // This are all just primitives, copy is fine
        this->layerAmount = cData.layerAmount;
        this->layerSize = cData.layerSize;
        this->props = cData.props;
    }

    
    bool isNull(){
        return layerAmount == 0;
    }
};


/* 
Used to create and represent canvas objects.

Features:
- Canvas are formed by an array of `RenderTexture2D`, allowing multiple layers 
- Canvas are rendered using a `Camera2D` space defined in `canvasView`, allowing to change the angle the canvas is seen
- Ability to export/import a Canvas using a `CanvasData` object
*/
class Canvas
{
    RenderTexture2D layers[MAX_LAYERS];
    size_t currenLayerIdx=0, layerAmount=1;

    // Canvas position in window
    Vector2 cPos = (Vector2){0, 0};
    int width, height;
    bool changed = false;
    
    void _makeBlank();

public:
    Camera2D canvasView;

    Canvas(int width, int height);
    Canvas(const Vector2 &size);
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


    // Returns all the relevant data as a `CanvasData` object
    CanvasData _getData();
    void _setData(const CanvasData &c);

    /*
        Turns Screen coordinates to Canvas coordinates, 
        used to get the coordinates where we should draw
    */
    inline Vector2 localCoord(const Vector2 &coord) 
    { 
        // Gets the Camera Matrix and multiplies coord by it
        return GetScreenToWorld2D(coord, canvasView);
    };
};
