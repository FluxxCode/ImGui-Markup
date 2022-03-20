#include "impch.h"
#include "items/item_base.h"

namespace igm::internal
{

ItemBase::ItemBase(
    ItemType type,
    ItemCategory category,
    std::string id,
    ItemBase* parent)
    : type_(type), category_(category), access_id_(id), parent_(parent)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->draw_id_ = ss.str();
}

void ItemBase::Update(Float2 position, Float2 size)
{
    ImGui::PushID(this);
    this->IMPL_Update(position, size);
    ImGui::PopID();
}

AttributeBase* ItemBase::GetAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return nullptr;

    return this->attribute_list_.at(name);
}

void ItemBase::AddAttribute(const std::string name, AttributeBase* attribute)
{
    if (this->attribute_list_.find(name) != this->attribute_list_.end())
    {
        internal::utils::Log(
            "WARNING: Item \"" + ItemTypeToString(this->type_) +
            "\": Attribute \"" + name +
            "\" is already set in attribute list!");

        return;
    }

    this->attribute_list_[name] = attribute;
}

void ItemBase::RemoveAttribute(const std::string name)
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
    {
        internal::utils::Log(
            "WARNING: Item \"" + ItemTypeToString(this->type_) +
            "\": Attribute \"" + name +
            "\" does not exists in the attribute list!");

        return;
    }

    this->attribute_list_.erase(name);
}

void ItemBase::AddChild(std::shared_ptr<ItemBase> child)
{
    this->child_items_.push_back(child);
}

}  // namespace igm::internal
