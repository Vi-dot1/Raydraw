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
    int width, height;
    bool changed = false;
public:
    Canvas(int width, int height);
    ~Canvas();

    RenderTexture2D& getCurrentLayer();

    void changeLayer(size_t);
    void addLayer();

    void _draw(const float &_x, const float &_y);
    Image _exportImage();

    inline Vector2 localCoord(Vector2 &coord) { return {coord.x-cPos.x, coord.y-cPos.y}; };
};