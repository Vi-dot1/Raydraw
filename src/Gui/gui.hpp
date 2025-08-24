#pragma once

#include<functional>
extern "C"{
    #include"raylib.h"
}


class Panel
{
    Rectangle area;
    std::function<void(const Rectangle&)> callback;

public:
    Panel(std::function<void(const Rectangle&)> func, Rectangle _area) :
    callback(func), area(_area)
    {};

    void _draw();
    bool IsOverPanel(const Vector2&);
};

bool drawGui(); // Main call point for main, returns whenever or not the mouse was used
