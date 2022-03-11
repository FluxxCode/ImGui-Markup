#include "impch.h"
#include "items/other/item_float4.h"

namespace imgui_markup::internal
{

ItemFloat4::ItemFloat4(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kItemFloat4, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
