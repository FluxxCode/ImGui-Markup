#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_

#include "items/item_base.h"

#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float4.h"

namespace imgui_markup::internal
{

class DrawableBase : public ItemBase
{
public:
    DrawableBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kDrawable, id, parent)
    { }

    DrawableBase(const DrawableBase&) = delete;

protected:
    void BeginItemArea(Float2 position, Float2 size);
    void EndItemArea(Float2 size, Float2 actual_item_size);

private:
    const Float2 window_padding_  = Float2(0.0f, 0.0f);
    const Float  window_rounding_ = 0;
    const Float4 window_bg_color_ = Float4(0.0f, 0.0f, 0.0f, 0.0f);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_
