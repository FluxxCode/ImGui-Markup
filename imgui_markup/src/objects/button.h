#ifndef IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
#define IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_

#include "objects/common/object_base.h"

#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

class ButtonStyle;

class Button : public ObjectBase
{
public:
    Button(std::string id, ObjectBase* parent);

    Button& operator=(const Button& other);

    String text_;

private:
    friend class ButtonStyle;
    ButtonStyle* style_ = nullptr;

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

#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
