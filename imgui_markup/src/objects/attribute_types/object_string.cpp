#include "impch.h"
#include "objects/attribute_types/object_string.h"

namespace imgui_markup::internal{

ObjectString:: ObjectString(std::string id, ObjectBase* parent)
    : ObjectBase("String", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectString& ObjectString::operator=(const ObjectString& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup::internal