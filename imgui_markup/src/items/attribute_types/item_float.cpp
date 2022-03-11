#include "impch.h"
#include "items/attribute_types/item_float.h"

namespace imgui_markup::internal
{

ItemFloat::ItemFloat(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kItemFloat, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
