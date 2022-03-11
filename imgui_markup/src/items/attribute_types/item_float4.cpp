#include "impch.h"
#include "items/attribute_types/item_float4.h"

namespace imgui_markup::internal
{

ItemFloat4::ItemFloat4(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kItemFloat4, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
