#include "impch.h"
#include "objects/common/object_base.h"

namespace imgui_markup::internal{

ObjectBase::ObjectBase(std::string name, std::string id, ObjectBase* parent)
    : type_(name), id_(id), parent_(parent)
{ }

ObjectBase& ObjectBase::operator=(const ObjectBase& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

Attribute* ObjectBase::GetAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return nullptr;

    return this->attribute_list_.at(name);
}

void ObjectBase::SetPosition(Float2 draw_position, Float2 global_offset)
{
    this->draw_position_ = draw_position;
    this->global_position_ = Float2(draw_position.x + global_offset.x,
                                    draw_position.y + global_offset.y);

    if (!this->parent_)
        return;

    const Float2 parent_position = this->parent_->GetDrawPosition();

    this->relative_position_ = Float2(draw_position.x - parent_position.x,
                                      draw_position.y - parent_position.y);
}

void ObjectBase::AddAttribute(const std::string name, Attribute* attribute)
{
    if (this->attribute_list_.find(name) != this->attribute_list_.end())
    {
        internal::utils::Log("WARNING: Object \"" + this->type_ +
            "\": Attribute \"" + name + "\" is already set in attribute list!");

        return;
    }

    this->attribute_list_[name] = attribute;
}

void ObjectBase::RemoveAttribute(const std::string name)
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
    {
        internal::utils::Log("WARNING: Object \"" + this->type_ +
            "\": Attribute \"" + name +
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