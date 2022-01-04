#include "ilpch.h"
#include "imgui_layer/objects/common/object.h"

namespace gui
{

Object::Object(std::string name, std::string id, Object* parent)
    : type_(name), id_(id), parent_(parent)
{
    this->attribute_list_ = {
        { "position", &this->position_ },
        { "size",     &this->size_ }
    };
}

Attribute* Object::GetAttribute(const std::string name) const
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
        return nullptr;

    return this->attribute_list_.at(name);
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
        utils::Log("WARNING: Object \"" + this->type_ + "\": Attribute \"" +
                   name + "\" is already set in attribute list!");
        return;
    }

    this->attribute_list_[name] = attribute;
}

void Object::RemoveAttribute(const std::string name)
{
    if (this->attribute_list_.find(name) == this->attribute_list_.end())
    {
        utils::Log("WARNING: Object \"" + this->type_ + "\": Attribute \"" +
                   name + "\" does not exists in the attribute list!");
        return;
    }

    this->attribute_list_.erase(name);
}

void Object::AddChild(std::shared_ptr<Object> child)
{
    this->child_objects_.push_back(child);
}

}  // namespace gui
