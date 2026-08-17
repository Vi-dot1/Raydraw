#pragma once

#include <string>
#include "gui.hpp"
#include "raylib.h"

namespace Gui {

class Label : public Gui::Component {
public: 
    std::string text;
    void draw();
};

class TextButton : public Gui::Component {
public: 
    std::string text;
    void draw();
};

class ColorButton : public Gui::Component {
public: 
    Color color;
    void draw();
};

class ImageButton : public Gui::Component {
public: 
    Texture2D src;
    void draw();
};

class ColorPicker : public Gui::Component {
public: 
    void draw();
    
    Color color = RAYWHITE;
};

/*
class HSlider : public Gui::Component {
public: 
    void draw();
};

class VSlider : public Gui::Component {
public: 
    void draw();
};

*/

}