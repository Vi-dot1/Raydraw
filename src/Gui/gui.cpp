extern "C"{
    #include"raylib.h"
}
#include "gui.hpp"

namespace Gui
{

void Panel::updatePanel(const Rectangle& rect)
{
    space = rect;
    for(Component* comp : comps)
    {
        comp->updateRect(space);
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
    comps.back()->updateRect(space);
}

}