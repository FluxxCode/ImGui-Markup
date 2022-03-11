#include "impch.h"
#include "items/other/item_float.h"

namespace imgui_markup::internal
{

ItemFloat::ItemFloat(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemFloat, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
