#include "impch.h"
#include "items/attribute_types/item_string.h"

namespace imgui_markup::internal
{

ItemString:: ItemString(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kItemString, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
