#ifndef IMGUI_MARKUP_SRC_OBJECTS_CHECKBOX_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CHECKBOX_H_

#include "objects/common/object_base.h"

#include "attribute_types/string.h"
#include "attribute_types/bool.h"

namespace imgui_markup::internal
{

class Checkbox : public ObjectBase
{
public:
    Checkbox(std::string id, ObjectBase* parent);

    Checkbox& operator=(const Checkbox& other);

    String text_;
    Bool is_toggled_ = false;

private:
    bool is_hovered_ = false;

    // See object.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See object_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
    Bool API_IsToggled() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_CHECKBOX_H_
