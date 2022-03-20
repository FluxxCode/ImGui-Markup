#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT2_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT2_H_

#include "items/common/other_base.h"
#include "attribute_types/float2.h"

namespace igm::internal
{

struct ItemFloat2 : public OtherBase
{
    ItemFloat2(std::string id, ItemBase* parent);
    ItemFloat2(const ItemFloat2&) = delete;

    Float2 value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT2_H_
