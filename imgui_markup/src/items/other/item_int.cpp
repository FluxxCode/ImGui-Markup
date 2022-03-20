#include "impch.h"
#include "items/other/item_int.h"

namespace igm::internal
{

ItemInt::ItemInt(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemInt, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace igm::internal
