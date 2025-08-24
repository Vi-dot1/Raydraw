#include "canvas.hpp"

Canvas::Canvas(int _width, int _height)
    : width(_width), height(_height)
{
    layers[0] = LoadRenderTexture(width, height);

    // Filling first layer
    BeginTextureMode(layers[0]);
    ClearBackground(RAYWHITE);
    EndTextureMode();
}

Image Canvas::_exportImage()
{
    RenderTexture2D r = LoadRenderTexture(layers[0].texture.width, layers[0].texture.height);


    BeginTextureMode(r);
    this->_draw(0, 0);
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

void Canvas::_draw(const float &_x, const float &_y)
{
    //if(!changed) return;

    for(size_t i=0; i<layerAmount; ++i)
    {
		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(layers[i].texture, 
            (Rectangle){0,0, (float)layers[0].texture.width, (float)-layers[0].texture.height }, 
            (Vector2){_x, _y}, 
            WHITE);
    }

    // Set canvas position with given coordinates in case they changed
    cPos.x = _x;
    cPos.y = _y;
}