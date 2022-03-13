#ifndef IMGUI_MARKUP_SRC_ITEMS_VIEWS_STACK_VIEW_H_
#define IMGUI_MARKUP_SRC_ITEMS_VIEWS_STACK_VIEW_H_

#include "items/common/view_base.h"
#include "common/enum_conversion.h"

#include "attribute_types/float2.h"
#include "attribute_types/enum.h"


namespace imgui_markup::internal
{

class StackView : public ViewBase
{
public:
    // Constructor/Destructor
    StackView(std::string id, ItemBase* parent);
    StackView(const StackView&) = delete;

    Enum<enums::Orientation> orientation_ = enums::Orientation::kVertical;
    Float2 padding_ = Float2(0.0f, 0.0f);
    Float item_spacing_ = Float(0.0f);

private:
    bool is_hovered_ = false;

    bool in_panel_ = false;
    const bool border_ = true;

    Float2 child_position_ = Float2(0.0f, 0.0f);
    Float2 child_size_ = Float2(0.0f, 0.0f);

    bool init_attributes_ = true;
    void InitAttributes();

    void BeginChild(Float2 position, Float2 size);
    void EndChild(Float2 size, Float2 actual_item_size);

    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);

    // See item_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_VIEWS_STACK_VIEW_H_
