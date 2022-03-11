#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_INT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_INT_H_

#include "items/common/item_base.h"
#include "attribute_types/int.h"

namespace imgui_markup::internal
{

struct ItemInt : public ItemBase
{
    ItemInt(std::string id, ItemBase* parent);
    ItemInt(const ItemInt&) = delete;

    Int value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_INT_H_
