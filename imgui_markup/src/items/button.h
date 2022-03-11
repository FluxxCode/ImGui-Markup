#ifndef IMGUI_MARKUP_SRC_ITEMS_BUTTON_H_
#define IMGUI_MARKUP_SRC_ITEMS_BUTTON_H_

#include "items/common/item_base.h"

#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

class ButtonStyle;

class Button : public ItemBase
{
public:
    Button(std::string id, ItemBase* parent);
    Button(const Button&) = delete;

    String text_;

private:
    friend class ButtonStyle;
    ButtonStyle* style_ = nullptr;

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

#endif  // IMGUI_MARKUP_SRC_ITEMS_BUTTON_H_
