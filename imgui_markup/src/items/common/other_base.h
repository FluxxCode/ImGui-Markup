#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_OTHER_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_OTHER_BASE_H_

#include "items/item_base.h"

namespace igm::internal
{

struct OtherBase : public ItemBase
{
    OtherBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kOther, id, parent)
    { }

    OtherBase(const OtherBase&) = delete;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_OTHER_OTHER_BASE_H_
