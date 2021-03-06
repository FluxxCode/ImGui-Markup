#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT4_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT4_H_

#include "items/common/other_base.h"
#include "attribute_types/float4.h"

namespace igm::internal
{

struct ItemFloat4 : public OtherBase
{
    ItemFloat4(std::string id, ItemBase* parent);
    ItemFloat4(const ItemFloat4&) = delete;

    Float4 value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_FLOAT4_H_
