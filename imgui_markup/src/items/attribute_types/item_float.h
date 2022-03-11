#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT_H_

#include "items/common/item_base.h"
#include "attribute_types/float.h"

namespace imgui_markup::internal
{

struct ItemFloat : public ItemBase
{
    ItemFloat(std::string id, ItemBase* parent);
    ItemFloat(const ItemFloat&) = delete;

    Float value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_FLOAT_H_
