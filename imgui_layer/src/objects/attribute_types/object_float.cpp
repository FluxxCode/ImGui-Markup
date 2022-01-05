#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_float.h"

namespace gui
{

ObjectFloat::ObjectFloat(std::string id, Object* parent)
    : Object("Float", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectFloat& ObjectFloat::operator=(const ObjectFloat& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace gui
