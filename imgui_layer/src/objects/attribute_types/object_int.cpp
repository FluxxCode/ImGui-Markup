#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_int.h"

namespace gui
{

ObjectInt::ObjectInt(std::string id, Object* parent)
    : Object("Int", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectInt& ObjectInt::operator=(const ObjectInt& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace gui
