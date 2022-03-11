#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_STRING_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_STRING_H_

#include "items/common/item_base.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

struct ItemString : public ItemBase
{
    ItemString(std::string id, ItemBase* parent);
    ItemString(const ItemString&) = delete;

    String value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_ATTRIBUTE_TYPES_ITEM_STRING_H_
