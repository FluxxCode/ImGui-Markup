#include "impch.h"
#include "objects/attribute_types/object_float3.h"

namespace imgui_markup::internal
{

ObjectFloat3::ObjectFloat3(std::string id, ObjectBase* parent)
    : ObjectBase("Float3", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectFloat3& ObjectFloat3::operator=(const ObjectFloat3& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup::internal
