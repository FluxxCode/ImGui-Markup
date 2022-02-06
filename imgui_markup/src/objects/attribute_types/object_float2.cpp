#include "impch.h"
#include "objects/attribute_types/object_float2.h"

namespace imgui_markup
{

ObjectFloat2::ObjectFloat2(std::string id, Object* parent)
    : Object("Float2", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectFloat2& ObjectFloat2::operator=(const ObjectFloat2& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup
