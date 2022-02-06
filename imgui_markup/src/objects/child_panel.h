#ifndef IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H

#include "objects/common/object.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal{

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
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H
