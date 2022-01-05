#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_float4.h"

namespace gui
{

ObjectFloat4::ObjectFloat4(std::string id, Object* parent)
    : Object("Float4", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectFloat4& ObjectFloat4::operator=(const ObjectFloat4& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace gui
