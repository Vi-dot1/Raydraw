#include "Gui/gui.hpp"
#include "State/mouse.hpp"
#include"raylib.h"

#define RAYGUI_IMPLEMENTATION 1
#include"raygui.h"
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
    // Update control
    //--------------------------------------------------------------------
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

    GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH)/2, GetColor(GuiGetStyle(BUTTON, BORDER + (state*3))), color);
}