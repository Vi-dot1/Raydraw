#include "canvas.h"

Canvas::Canvas(int width, int height)
{
    layers[0] = LoadRenderTexture(width, height);
    
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

void Canvas::_draw(const int &_x, const int &_y)
{
    for(size_t i=0; i<layerAmount; ++i)
    {
		// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(layers[i].texture, 
            (Rectangle){_x,_y, (float)layers[0].texture.width, (float)-layers[0].texture.height }, 
            (Vector2){0,0}, 
            WHITE);
    }
    cPos.x = _x;
    cPos.y = _y;
}