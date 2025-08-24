extern "C"{
    #include"raylib.h"

    #define RAYGUI_IMPLEMENTATION 1
    #include"raygui.h"
}

#include"Brush/brush.hpp"
#include"gui.hpp"

bool drawGui()
{
    auto content1 = [](const Rectangle &r) {
        GuiColorPicker((Rectangle){ 5, 10, r.width-45, 162 }, nullptr, &(Brush::brushColor));
        GuiSlider((Rectangle){0, 192, 192, 20}, nullptr, nullptr, &(Brush::brushSize), 0, 20);
    };

    Panel panel1(content1, (Rectangle){0, 0, 200, (float)GetScreenHeight()});
    panel1._draw();

    return panel1.IsOverPanel(GetMousePosition());
}

// GuiPanel
void Panel::_draw()
{
    if(callback == nullptr) return;
    BeginScissorMode(area.x, area.y, area.width, area.height);
    callback(area);
    EndScissorMode();
};
bool Panel::IsOverPanel(const Vector2 &point) { return CheckCollisionPointRec(point, area); }

/*
void GuiWindowFloating(Rectangle &place, void (*draw)(Vector2, Vector2), Vector2 content_size, const char* title)
{
    const int WBAR_HEIGHT = 24;
    const int BARBUTTON_SIZE = 18;

    static bool moving = false;
    static bool resizing = false;

    if( moving )
    {
        moving = !IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

        Vector2 mdelta = GetMouseDelta();
        place.x += mdelta.x;
        place.y += mdelta.y;

        // Keep Window inside the screen
        if(place.x < 0) place.x = 0;
        if(place.x+place.width > GetScreenWidth()) place.x = GetScreenWidth()-place.width;
        if(place.y < 0) place.y = 0;
        if(place.x+place.height > GetScreenHeight()) place.y = GetScreenHeight()-place.height;
    }
    else if( resizing )
    {
        resizing = !IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

        const int arbitraryMin = 200;
        if( place.width < arbitraryMin ) place.width = arbitraryMin;
        if( place.width > GetScreenWidth() ) place.width = GetScreenWidth()-arbitraryMin;

        if( place.height < arbitraryMin ) place.height = arbitraryMin;
        if( place.height > GetScreenHeight() ) place.height = GetScreenHeight()-arbitraryMin;
    }

    GuiWindowBox(place, title);
    if( draw != nullptr )
    {
        BeginScissorMode(place.x, place.y, place.width, place.height);
        draw((Vector2){place.x, place.y}, (Vector2){place.width, place.height});
        EndScissorMode();
    }

}
*/