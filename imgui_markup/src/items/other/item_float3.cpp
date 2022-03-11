#include "impch.h"
#include "items/other/item_float3.h"

namespace imgui_markup::internal
{

ItemFloat3::ItemFloat3(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemFloat3, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
