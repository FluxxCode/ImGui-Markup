#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT3_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT3_H_

#include "items/common/other_base.h"
#include "attribute_types/float3.h"

namespace igm::internal
{

struct ItemFloat3 : public OtherBase
{
    ItemFloat3(std::string id, ItemBase* parent);
    ItemFloat3(const ItemFloat3&) = delete;

    Float3 value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT3_H_
