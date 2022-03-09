#include "impch.h"
#include "objects/common/object_base.h"

namespace imgui_markup::internal
{

ObjectBase::ObjectBase(std::string name, std::string id, ObjectBase* parent)
    : type_(name), access_id_(id), parent_(parent)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->draw_id_ = ss.str();
}

void ObjectBase::Update(Float2 position, Float2 size)
{
    this->position_ = position;
    this->size_ = size;

    ImGui::PushID(this);
    this->IMPL_Update(position, size);
    ImGui::PopID();
}

AttributeBase* ObjectBase::GetAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return nullptr;

    return this->attribute_list_.at(name);
}

void ObjectBase::AddAttribute(const std::string name, AttributeBase* attribute)
{
    if (this->attribute_list_.find(name) != this->attribute_list_.end())
    {
        internal::utils::Log("WARNING: Object \"" + this->type_ +
            "\": AttributeBase \"" + name + "\" is already set in attribute list!");

        return;
    }

    this->attribute_list_[name] = attribute;
}

void ObjectBase::RemoveAttribute(const std::string name)
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
    {
        internal::utils::Log("WARNING: Object \"" + this->type_ +
            "\": AttributeBase \"" + name +
            "\" does not exists in the attribute list!");

        return;
    }

    this->attribute_list_.erase(name);
}

void ObjectBase::AddChild(std::shared_ptr<ObjectBase> child)
{
    this->child_objects_.push_back(child);
}

}  // namespace imgui_markup::internal
