#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_VIEW_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_VIEW_BASE_H_

#include "items/item_base.h"

namespace igm::internal
{

struct ViewBase : public ItemBase
{
    ViewBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kView, id, parent)
    { }

    ViewBase(const ViewBase&) = delete;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_COMMON_VIEW_BASE_H_
