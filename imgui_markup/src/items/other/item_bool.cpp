#include "impch.h"
#include "items/other/item_bool.h"

namespace imgui_markup::internal
{

ItemBool::ItemBool(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemBool, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
