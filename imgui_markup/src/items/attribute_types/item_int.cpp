#include "impch.h"
#include "items/attribute_types/item_int.h"

namespace imgui_markup::internal
{

ItemInt::ItemInt(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kItemInt, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
