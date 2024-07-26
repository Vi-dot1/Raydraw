extern "C"{
    #include"raylib.h"

    #define RAYGUI_IMPLEMENTATION 1
    #include"raygui.h"
}

#include"brush.h"
#include"gui.h"
void drawGui()
{
    static bool showMessageBox = false;

    // Third GUI column
    GuiColorPicker((Rectangle){ 0, 0, 196, 192 }, nullptr, &(Brush::brushColor));
}