#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_BOOL_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_BOOL_H_

#include "items/common/other_base.h"
#include "attribute_types/bool.h"

namespace igm::internal
{

struct ItemBool : public OtherBase
{
    ItemBool(std::string id, ItemBase* parent);
    ItemBool(const ItemBool&) = delete;

    Bool value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_BOOL_H_
