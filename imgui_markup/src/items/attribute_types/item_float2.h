#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT2_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT2_H_

#include "items/common/item_base.h"
#include "attribute_types/float2.h"

namespace imgui_markup::internal
{

struct ItemFloat2 : public ItemBase
{
    ItemFloat2(std::string id, ItemBase* parent);
    ItemFloat2(const ItemFloat2&) = delete;

    Float2 value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT2_H_
