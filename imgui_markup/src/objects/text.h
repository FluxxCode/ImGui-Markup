#ifndef IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
#define IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_

#include "objects/common/object_base.h"

#include "attribute_types/float4.h"
#include "attribute_types/float2.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

class Text : public ObjectBase
{
public:
    // Constructor/Destructor
    Text(std::string id, ObjectBase* parent);
    Text(const Text&) = delete;

    String text_;
    Float4 color_;

private:
    bool is_hovered_ = false;

    // See object.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See object_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
