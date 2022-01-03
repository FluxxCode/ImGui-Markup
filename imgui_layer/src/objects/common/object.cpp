#include "ilpch.h"
#include "imgui_layer/objects/common/object.h"

namespace gui
{

Object::Object(std::string name, std::string id, Object* parent)
    : name_(name), id_(id), parent_(parent)
{
    this->attribute_list_ = {
        { "position", &this->position_ },
        { "size",     &this->size_ }
    };
}

bool Object::SetAttributeValue(const std::string name, const Attribute& value)
{
    if (!this->HasAttribute(name))
        return false;

    return this->attribute_list_.at(name)->LoadValue(value);
}

Attribute* Object::GetAttribute(const std::string name) const
{
    if (!this->HasAttribute(name))
        return nullptr;

    return this->attribute_list_.at(name);
}

bool Object::HasAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return false;

    return true;
}

bool Object::HasParent()
{
    return this->parent_ ? true : false;
}

Object* Object::GetParent() const
{
    return this->parent_;
}

std::shared_ptr<Object> Object::GetChild(
    const std::string id,
    bool recursive) const
{
    for (unsigned int i = 0; i < this->child_objects_.size(); i++)
    {
        if (this->child_objects_[i]->GetID() == id)
            return this->child_objects_[i];

        if (recursive)
        {
            std::shared_ptr<Object> obj =
                this->child_objects_[i]->GetChild(id, true);

            if (obj)
                return obj;
        }
    }

    return nullptr;
}

void Object::AddChild(std::shared_ptr<Object> child)
{
    this->child_objects_.push_back(child);
}

std::string Object::GetName() const
{
    return this->name_;
}

std::string Object::GetID() const
{
    return this->id_;
}

void Object::UpdateChilds()
{
    for (unsigned int i = 0; i < this->child_objects_.size(); i++)
        this->child_objects_[i]->Update();
}

void Object::AddAttribute(const std::string name, Attribute* attribute)
{
    if (this->attribute_list_.find(name) != this->attribute_list_.end())
    {
        utils::Log("WARNING: Object \"" + this->name_ + "\": Attribute \"" +
                   name + "\" is already set in attribute list!");
        return;
    }

    this->attribute_list_[name] = attribute;
}

void Object::RemoveAttribute(const std::string name)
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
    {
        utils::Log("WARNING: Object \"" + this->name_ + "\": Attribute \"" +
                   name + "\" does not exists in the attribute list!");
        return;
    }

    this->attribute_list_.erase(name);
}

}  // namespace gui
