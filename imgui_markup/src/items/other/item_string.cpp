#include "impch.h"
#include "items/other/item_string.h"

namespace igm::internal
{

ItemString:: ItemString(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemString, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace igm::internal
