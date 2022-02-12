#include "impch.h"
#include "objects/attribute_types/object_float4.h"

namespace imgui_markup::internal{

ObjectFloat4::ObjectFloat4(std::string id, ObjectBase* parent)
    : ObjectBase("Float4", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectFloat4& ObjectFloat4::operator=(const ObjectFloat4& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup::internal