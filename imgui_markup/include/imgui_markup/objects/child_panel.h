#ifndef IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H_
#define IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H

#include "imgui_markup/objects/common/object.h"

#include "imgui_markup/attribute_types/bool.h"
#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
{

class ChildPanel : public Object
{
public:
    // Constructor/Destructor
    ChildPanel(std::string id, Object* parent);

    ChildPanel& operator=(const ChildPanel& other);

    // Functions
    void Update();

    String title_;
    Bool border_;

private:
    // See object.h for documentation
   bool OnProcessEnd(std::string& error_message);
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_SRC_OBJECTS_CHILD_PANEL_H
