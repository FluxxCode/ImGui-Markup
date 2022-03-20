#include "impch.h"
#include "items/other/item_bool.h"

namespace igm::internal
{

ItemBool::ItemBool(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemBool, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace igm::internal
