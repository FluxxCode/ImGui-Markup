#include "impch.h"
#include "items/item_mapping.h"

namespace igm::internal
{

bool StringToItemType(std::string str, ItemType& out)
{
    if (item_types::item_mapping.find(str) !=
        item_types::item_mapping.end())
    {
        out = item_types::item_mapping.at(str);
        return true;
    }

    return false;
}

std::string ItemTypeToString(ItemType obj)
{
    for (const auto& element : item_types::item_mapping)
    {
        if (element.second == obj)
            return element.first;
    }

    return std::string();
}

}  // namespace igm::internal
