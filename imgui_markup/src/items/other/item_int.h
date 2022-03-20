#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_INT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_INT_H_

#include "items/common/other_base.h"
#include "attribute_types/int.h"

namespace igm::internal
{

struct ItemInt : public OtherBase
{
    ItemInt(std::string id, ItemBase* parent);
    ItemInt(const ItemInt&) = delete;

    Int value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_INT_H_
