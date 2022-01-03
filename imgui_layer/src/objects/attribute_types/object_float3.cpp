#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_float3.h"

namespace gui
{

ObjectFloat3::ObjectFloat3(std::string id, Object* parent)
    : Object("Float3", id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace gui
