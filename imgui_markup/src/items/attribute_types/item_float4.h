#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT4_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT4_H_

#include "items/common/item_base.h"
#include "attribute_types/float4.h"

namespace imgui_markup::internal
{

struct ItemFloat4 : public ItemBase
{
    ItemFloat4(std::string id, ItemBase* parent);
    ItemFloat4(const ItemFloat4&) = delete;

    Float4 value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT4_H_
