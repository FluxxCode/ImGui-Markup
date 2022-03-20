#ifndef IMGUI_MARKUP_SRC_ITEMS_COMMON_CONTAINER_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_COMMON_CONTAINER_BASE_H_

#include "items/item_base.h"

namespace igm::internal
{

struct ContainerBase : public ItemBase
{
    ContainerBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kContainer, id, parent)
    { }

    ContainerBase(const ContainerBase&) = delete;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_COMMON_CONTAINER_BASE_H_
