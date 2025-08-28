extern "C"{
    #include"raylib.h"

    #define RAYGUI_IMPLEMENTATION 1
    #include"raygui.h"
}

#include"Brush/tool.hpp"
#include"gui.hpp"


// Proportion of the screen the panel occupies horizontally
static float panelWidthScale = 0.22; 

static Rectangle panelArea;
float panelHMarging = 6;
float panelVMarging = 4;
float fontHeight = 18;

// If there's squares, this should be their dimensions
float panelSquareSize = panelArea.width-panelHMarging*2;

// Witdth and height of all sliders
Vector2 panelSlider = {panelArea.width-panelHMarging*2, fontHeight };

namespace Gui
{

const int MAX_COLORS = 16;
const int COLOR_PER_ROW = sqrt(MAX_COLORS);
float colorBoxSize = (panelSquareSize)/COLOR_PER_ROW;
static Color SavedColors[MAX_COLORS] =  {
    PINK,
    RED,
    BLUE,
    SKYBLUE,
    YELLOW,
    GOLD,
    ORANGE,
    DARKGREEN,
    GREEN,
    LIME,
    MAGENTA,
    PURPLE,
    BEIGE,
    BROWN,
    DARKBROWN,
    BLACK,
};
int currentColor = 0;


bool drawGui(const Vector2 &mpos)
{
    bool isMouseOnScreen = false;


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

        SavedColors[currentColor] = Tool::color;

        GuiLabel(
            (Rectangle)
            {
                panelHMarging,
                panelSquareSize,
                panelSlider.x, panelSlider.y
            }, 
            "Colors"
        );
        // Brush Size, also havin some weird positioning due to the color picker...
        GuiSlider(
            (Rectangle)
                {
                    panelHMarging, panelSquareSize-panelVMarging, 
                    panelSlider.x, panelSlider.y
                }, 

            nullptr, nullptr, &(Tool::size), 
            1, 20
        );

        // Individual color boxes
        const Vector2 colorBoxPos = {panelHMarging, panelSquareSize+fontHeight};

        for(int i=0, color_idx=0; i<panelSquareSize-1 && color_idx<MAX_COLORS; i+=colorBoxSize)
        {
            for(int j=0; j<panelSquareSize; j+=colorBoxSize)
            {

                Rectangle colorBox = (Rectangle)
                {
                    colorBoxPos.x+j, colorBoxPos.y+i, 
                    colorBoxSize, colorBoxSize
                };

                // The only way I found to show the color in the button is to draw a rectangle on top of it
                // with the way raygui works means I must draw a button, then the rectangle with the color on top
                // that means there's overdraw, there may be ways to optimize this
                bool picked = currentColor == color_idx;
                picked |= GuiButton
                (
                    colorBox,
                    nullptr
                );
                DrawRectangleRec(
                    colorBox,
                    SavedColors[color_idx]
                );

                if( picked ) 
                {
                    DrawRectangleLinesEx(colorBox, 2, RAYWHITE);
                    currentColor = color_idx;
                }
                ++color_idx;
            }
        }
        Tool::color = SavedColors[currentColor];
        

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
    panelArea.width = ( GetScreenWidth()*panelWidthScale );

    // If there's squares, this should be their dimensions
    panelSquareSize = panelArea.width-panelHMarging*2;

    colorBoxSize = (panelSquareSize)/COLOR_PER_ROW;

    // Witdth and height of all sliders
    panelSlider = {panelArea.width-panelHMarging*2, fontHeight };
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