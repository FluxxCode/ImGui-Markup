#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_float4.h"

namespace gui
{

ObjectFloat4::ObjectFloat4(std::string id, Object* parent)
    : Object("Float4", id, parent)
{
    this->AddAttribute("value", &this->value);

    this->RemoveAttribute("position");
    this->RemoveAttribute("size");
}

}  // namespace gui
