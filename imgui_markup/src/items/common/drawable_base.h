#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_

#include "items/item_base.h"

namespace imgui_markup::internal
{

struct DrawableBase : public ItemBase
{
    DrawableBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kDrawable, id, parent)
    { }

    DrawableBase(const DrawableBase&) = delete;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_COMMON_DRAWABLE_BASE_H_
