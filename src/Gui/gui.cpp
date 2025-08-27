extern "C"{
    #include"raylib.h"

    #define RAYGUI_IMPLEMENTATION 1
    #include"raygui.h"
}

#include"Brush/tool.hpp"
#include"gui.hpp"


// Proportion of the screen the panel occupies horizontally
static float panelWidthScale = 0.20; 

static Rectangle panelArea;
float panelHMarging = 6;
float panelVMarging = 4;
float fontHeight = 18;

namespace Gui
{


bool drawGui(const Vector2 &mpos)
{
    bool isMouseOnScreen = false;

    // If there's squares, this should be their dimensions
    float panelSquareSize = panelArea.width-panelHMarging*2;

    // Witdth and height of all sliders
    Vector2 panelSlider = {panelArea.width-panelHMarging*2, fontHeight };

    Color panelColor = (Color){112, 132, 122, 122};
    DrawRectanglePro(
        panelArea, 
        (Vector2){0,0}, 
        0.0, 
        panelColor
    );
    
    {
        // Raygui's color picker also draws a hue bar on the side out of the given rect,
        // So in order to make it fit on the panel I had to reduce its dimensions
        float colorPickerSize = panelSquareSize-fontHeight-panelHMarging;
        GuiColorPicker(
            (Rectangle)
            {
                panelHMarging, panelVMarging,
                colorPickerSize,
                colorPickerSize 
            },
            nullptr, 
            &(Tool::color)
        );

        // Brush Size, also havin some weird positioning due to the color picker...
        GuiSlider(
            (Rectangle)
                {
                    panelHMarging, panelSquareSize, 
                    panelSlider.x, panelSlider.y
                }, 

            nullptr, nullptr, &(Tool::size), 
            1, 20
        );
    }

    // For the moments is an or, I'll maybe draw another panel on the right for layers
    isMouseOnScreen |= CheckCollisionPointRec(mpos, panelArea);

    return isMouseOnScreen;
}

void updatePanel()
{
    // For the moments, the panel is eternally
    // attached to the top left
    panelArea.x = 0;
    panelArea.y = 0;

    panelArea.height = GetScreenHeight();
    panelArea.width = ( GetScreenWidth()*panelWidthScale ) - panelHMarging*2;
}

bool isInPanel(const Vector2 &pos)
{
    return CheckCollisionPointRec(pos, panelArea);
}

}
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