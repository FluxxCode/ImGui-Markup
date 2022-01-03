#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_bool.h"

namespace gui
{

ObjectBool::ObjectBool(std::string id, Object* parent)
    : Object("Bool", id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace gui
