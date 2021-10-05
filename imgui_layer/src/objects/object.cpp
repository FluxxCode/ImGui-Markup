#include "ilpch.h"
#include "objects/object.h"
#include "object.h"

namespace gui
{

Object::Object(std::string name, std::string id, Object* parent)
    : name_(name), id_(id), parent_(parent)
{ }

bool Object::SetAttributeValue(const std::string name, const std::string value)
{
    if (!this->HasAttribute(name))
    {
        this->last_error_ = ParserError(ParserError(
            ParserErrorType::kInvalidAttributeName,
            "Object \"" + this->name_ + "\" has no attribute called \"" +
            name + "\"."));

        return false;
    }

    if (!this->attribute_list_.at(name)->LoadValue(value))
    {
        this->last_error_ = this->attribute_list_.at(name)->GetLastError();
        return false;
    }

    return true;
}

AttributeType* Object::GetAttribute(const std::string name) const
{
    if (!this->HasAttribute(name))
    {
        this->last_error_ = ParserError(ParserError(
            ParserErrorType::kInvalidAttributeName,
            "Object \"" + this->name_ + "\" has no attribute called + \"" +
            name + "\"."));

        return nullptr;
    }

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

ParserError Object::GetLastError() const
{
    return this->last_error_;
}

void Object::UpdateChilds()
{
    for (unsigned int i = 0; i < this->child_objects_.size(); i++)
        this->child_objects_[i]->Update();
}

}  // namespace gui
