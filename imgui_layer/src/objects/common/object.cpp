#include "ilpch.h"
#include "imgui_layer/objects/common/object.h"

namespace gui
{

Object::Object(std::string name, std::string id, Object* parent)
    : type_(name), id_(id), parent_(parent)
{ }

Object& Object::operator=(const Object& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

Attribute* Object::GetAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return nullptr;

    return this->attribute_list_.at(name);
}

void Object::SetPosition(Float2 draw_position, Float2 global_offset)
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

Rect Object::GetVisibleRect() const
{
    Rect rect;
    rect.position = this->global_position_;
    rect.size     = this->size_;

    if (!this->parent_)
        return rect;

    const Rect parent_rect = this->parent_->GetVisibleRect();
    if (parent_rect.position.x > rect.position.x)
        rect.position.x = parent_rect.position.x;
    if (parent_rect.position.y > rect.position.y)
        rect.position.y = parent_rect.position.y;
    if (parent_rect.position.x + parent_rect.size.x <
        rect.position.x + rect.size.x)
    {
        rect.size.x = parent_rect.size.x;
    }
    if (parent_rect.position.y + parent_rect.size.y <
        rect.position.y + rect.size.y)
    {
        rect.size.y = parent_rect.size.y;
    }

    return rect;
}

void Object::AddAttribute(const std::string name, Attribute* attribute)
{
    if (this->attribute_list_.find(name) != this->attribute_list_.end())
    {
        internal::utils::Log("WARNING: Object \"" + this->type_ +
            "\": Attribute \"" + name + "\" is already set in attribute list!");

        return;
    }

    this->attribute_list_[name] = attribute;
}

void Object::RemoveAttribute(const std::string name)
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

void Object::AddChild(std::shared_ptr<Object> child)
{
    this->child_objects_.push_back(child);
}

}  // namespace gui
