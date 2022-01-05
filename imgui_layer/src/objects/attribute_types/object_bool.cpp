#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_bool.h"

namespace gui
{

ObjectBool::ObjectBool(std::string id, Object* parent)
    : Object("Bool", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectBool& ObjectBool::operator=(const ObjectBool& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace gui
