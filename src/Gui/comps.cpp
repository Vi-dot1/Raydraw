#include "State/mouse.hpp"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION 1
#include "raygui.h"
#include "comps.hpp"

using namespace Gui;

void Label::draw()
{
    GuiLabel(bounds, text.c_str());
}

void TextButton::draw()
{
    if( GuiButton(bounds, text.c_str()) )
        callback(*this);
}

void ColorButton::draw()
{
    int result = RESULT_NONE;
    GuiState state = guiState;
    if ((state != STATE_DISABLED) && !guiLocked && !guiControlExclusiveMode)
    {
        Vector2 mousePoint = Mouse::getPos();
        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (GUI_BUTTON_DOWN) state = STATE_PRESSED;
            else state = STATE_FOCUSED;
            if (GUI_BUTTON_RELEASED) result = RESULT_PRESSED;
        }
    }

    if( result )
        callback(*this);

    GuiDrawRectangle(
        bounds, 
        GuiGetStyle(BUTTON, BORDER_WIDTH)/2, 
        GetColor(GuiGetStyle(BUTTON, BORDER + (state*3))), 
        color
    );
}

void ImageButton::draw()
{
    int result = RESULT_NONE;
    GuiState state = guiState;
    if ((state != STATE_DISABLED) && !guiLocked && !guiControlExclusiveMode)
    {
        Vector2 mousePoint = Mouse::getPos();
        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (GUI_BUTTON_DOWN) state = STATE_PRESSED;
            else state = STATE_FOCUSED;
            if (GUI_BUTTON_RELEASED) result = RESULT_PRESSED;
        }
    }

    if( result )
        callback(*this);

    GuiDrawRectangle(
        bounds, 
        GuiGetStyle(BUTTON, BORDER_WIDTH)/2, 
        GetColor(GuiGetStyle(BUTTON, BORDER + (state*3))), 
        RAYWHITE
    );
    
    const int border = GuiGetStyle(BUTTON, BORDER_WIDTH)/2;
    DrawTexturePro(
        src, 
        {0,0, (float)src.width, (float)src.height}, 
        {bounds.x+border,bounds.y+border,bounds.width-border*2,bounds.height-border*2}, 
        {0,0}, 
        0, RAYWHITE
    );
}

void ColorPicker::draw()
{
    const Rectangle panelSpace = {bounds.x, bounds.y, bounds.width*0.85f, bounds.height*.9f};
    const Rectangle hsvSpace = {bounds.x+panelSpace.width, bounds.y, bounds.width*0.15f, panelSpace.height};
    const Rectangle alphaSpace = {bounds.x, bounds.y+panelSpace.height, bounds.width, panelSpace.height*.1f};
    
    GuiColorPanel(panelSpace, "", &color);

    Vector3 hsv = ConvertRGBtoHSV(
        RAYGUI_CLITERAL(Vector3)
        { color.r/255.0f, color.g/255.0f, color.b/255.0f }
    );
    GuiColorBarHue(hsvSpace, "", &hsv.x);

    float alpha = static_cast<float>(color.a);
    GuiSlider(alphaSpace, "", "", &alpha, 0, 255);
    
    Vector3 rgb = ConvertHSVtoRGB(hsv);
    color = RAYGUI_CLITERAL(Color){
        // RGB
        (unsigned char)roundf(rgb.x*255.0f), 
        (unsigned char)roundf(rgb.y*255.0f), 
        (unsigned char)roundf(rgb.z*255.0f), 
        
        // Alpha
        (unsigned char)roundf(alpha)
    };
}