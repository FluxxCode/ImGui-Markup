#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_OTHER_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_OTHER_BASE_H_

#include "items/item_base.h"

namespace imgui_markup::internal
{

struct OtherBase : public ItemBase
{
    OtherBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kOther, id, parent)
    { }

    OtherBase(const OtherBase&) = delete;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_OTHER_OTHER_BASE_H_
