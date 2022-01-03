#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_string.h"

namespace gui
{

ObjectString:: ObjectString(std::string id, Object* parent)
    : Object("String", id, parent)
{
    this->AddAttribute("value", &this->value);

    this->RemoveAttribute("position");
    this->RemoveAttribute("size");
}

}  // namespace gui
