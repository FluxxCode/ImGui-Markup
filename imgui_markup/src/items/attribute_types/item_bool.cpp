#include "impch.h"
#include "items/attribute_types/item_bool.h"

namespace imgui_markup::internal
{

ItemBool::ItemBool(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kItemBool, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
