#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_STYLE_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_STYLE_BASE_H_

#include "items/item_base.h"

namespace igm::internal
{

struct StyleBase : public ItemBase
{
    StyleBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kStyle, id, parent)
    { }

    StyleBase(const StyleBase&) = delete;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLES_STYLE_BASE_H_
