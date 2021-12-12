#ifndef IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H_
#define IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/attribute_types/bool.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{

class ChildPanel : public Object
{
public:
    // Constructor/Destructor
    ChildPanel(std::string id, Object* parent);

    // Functions
    void Update();

    String title_;
    Bool border_;

private:
    // Variables
    bool init_ = true;

    // Functions
    void Init();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H
