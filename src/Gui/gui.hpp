#pragma once

#include <functional>
#include <vector>

#include"raylib.h"

namespace Gui {

// I just feel is going to be useful in the future
// overengi... is just a struct come on

struct Component {
    float left=0.f, right=1.f, up=0.f, down=1.f;
    Rectangle bounds = {0,0,0,0};
    virtual void draw() = 0;
    
    std::function<void(Component&)> callback = [](Component& c){};

    // Calculate space inside panel using anchors
    // called automatically for `panel`
    void updateRect(Rectangle& panelSpace) {

        bounds.x = (panelSpace.width*left) + panelSpace.x;
        bounds.y = (panelSpace.height*up) + panelSpace.y;

        bounds.width = (panelSpace.width*(right-left));
        bounds.height = (panelSpace.height*(down-up));
    }
};

class Panel {
    Rectangle space;

    // I dont like this cache wise
    // but is just soo flexible
    std::vector<Component*> comps;
public:
    bool visible=true;

    void draw(); 
    void appendComp(Component* comp);

    // Updates screen space and recalculates 
    // components's size when resized
    void updatePanel(const Rectangle&);
};

}