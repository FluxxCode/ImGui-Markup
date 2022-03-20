#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_STRING_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_STRING_H_

#include "items/common/other_base.h"
#include "attribute_types/string.h"

namespace igm::internal
{

struct ItemString : public OtherBase
{
    ItemString(std::string id, ItemBase* parent);
    ItemString(const ItemString&) = delete;

    String value;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_ITEMS_OTHER_ITEM_STRING_H_
