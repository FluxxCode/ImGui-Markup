#ifndef IMGUI_MARKUP_SRC_ITEMS_TEXT_H_
#define IMGUI_MARKUP_SRC_ITEMS_TEXT_H_

#include "items/common/item_base.h"

#include "attribute_types/float4.h"
#include "attribute_types/float2.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

class Text : public ItemBase
{
public:
    // Constructor/Destructor
    Text(std::string id, ItemBase* parent);
    Text(const Text&) = delete;

    String text_;
    Float4 color_;

private:
    bool is_hovered_ = false;

    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See item_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_TEXT_H_
