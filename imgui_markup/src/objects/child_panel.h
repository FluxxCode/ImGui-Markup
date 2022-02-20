#ifndef IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H

#include "objects/common/object_base.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

class ChildPanel : public ObjectBase
{
public:
    // Constructor/Destructor
    ChildPanel(std::string id, ObjectBase* parent);

    ChildPanel& operator=(const ChildPanel& other);

    String title_;
    Bool border_;

private:
    bool is_hovered_ = false;

    // See object.h for documentation
    void IMPL_Update();
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See object_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_CHILD_PANEL_H
