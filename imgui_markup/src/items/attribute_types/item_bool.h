#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_BOOL_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_BOOL_H_

#include "items/common/item_base.h"
#include "attribute_types/bool.h"

namespace imgui_markup::internal
{

struct ItemBool : public ItemBase
{
    ItemBool(std::string id, ItemBase* parent);
    ItemBool(const ItemBool&) = delete;

    Bool value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_BOOL_H_
