#include "impch.h"
#include "items/other/item_float.h"

namespace igm::internal
{

ItemFloat::ItemFloat(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemFloat, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace igm::internal
