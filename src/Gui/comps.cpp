extern "C"{
    #include"raylib.h"

    #define RAYGUI_IMPLEMENTATION 1
    #include"raygui.h"
}

#include "comps.hpp"

using namespace Gui;

void Label::draw()
{
    GuiLabel(bounds, text.c_str());
}

void TextButton::draw()
{
    GuiButton(bounds, text.c_str());
}
