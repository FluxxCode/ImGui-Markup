#include "impch.h"
#include "items/common/item_list.h"

namespace imgui_markup::internal
{

std::shared_ptr<ItemBase> ItemList::CreateItem(
    std::string type,
    std::string id,
    ItemBase* parent)
{
    return ItemList::Get().IMPLCreateItem(type, id, parent);
}

bool ItemList::IsDefined(std::string type, ItemType* converted_type)
{
    return ItemList::Get().IMPLIsDefined(type, converted_type);
}

ItemList& ItemList::Get()
{
    static ItemList instance;
    return instance;
}

std::shared_ptr<ItemBase> ItemList::IMPLCreateItem(
    std::string type,
    std::string id,
    ItemBase* parent)
{
    ItemType converted_type;
    if (this->IsDefined(type, &converted_type))
        return this->item_list_.at(converted_type)(id, parent);

    return nullptr;
}

bool ItemList::IMPLIsDefined(std::string type, ItemType* converted_type)
{
    ItemType temp;

    if (!StringToItemType(type, temp))
        return false;

    if (this->item_list_.find(temp) == this->item_list_.end())
        return false;

    if (converted_type)
        *converted_type = temp;

    return true;
}

}  // namespace imgui_markup::internal
