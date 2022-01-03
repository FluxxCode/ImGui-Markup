#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_float2.h"

namespace gui
{

ObjectFloat2::ObjectFloat2(std::string id, Object* parent)
    : Object("Float2", id, parent)
{
    this->AddAttribute("value", &this->value);

    this->RemoveAttribute("position");
    this->RemoveAttribute("size");
}

}  // namespace gui
