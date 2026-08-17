extern "C"{
    #include"raylib.h"
}
#include "gui.hpp"

namespace Gui
{

void Panel::updateRect(const Rectangle& rect)
{
    bounds = rect;
    for(Component* comp : comps)
    {
        comp->updateRect(bounds);
    }
}
void Panel::draw()
{
    if( !visible ) return;
    for(Component* comp : comps)
    {
        comp->draw();
    }
}
void Panel::appendComp(Component* comp)
{
    comps.emplace_back(comp);
    comps.back()->updateRect(bounds);
}

}