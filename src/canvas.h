#pragma once

#include<cstddef>
extern "C"{
    #include "raylib.h"
}
#define MAX_LAYERS 80

class Canvas
{
    RenderTexture2D layers[MAX_LAYERS];
    size_t currenLayer=0, layerAmount=1;

    Vector2 cPos = (Vector2){0, 0};
public:
    Canvas(int width, int height);
    ~Canvas();

    RenderTexture2D& getCurrentLayer();

    void changeLayer(size_t);
    void addLayer();

    void _draw(const int &_x, const int &_y);
    Image _exportImage();
};