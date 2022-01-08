#include "impch.h"
#include "imgui_markup/objects/attribute_types/object_string.h"

namespace imgui_markup
{

ObjectString:: ObjectString(std::string id, Object* parent)
    : Object("String", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectString& ObjectString::operator=(const ObjectString& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup
