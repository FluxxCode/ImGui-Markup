#include "impch.h"
#include "items/other/item_float2.h"

namespace imgui_markup::internal
{

ItemFloat2::ItemFloat2(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemFloat2, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal