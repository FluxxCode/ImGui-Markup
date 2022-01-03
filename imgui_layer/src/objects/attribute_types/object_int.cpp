#include "ilpch.h"
#include "imgui_layer/objects/attribute_types/object_int.h"

namespace gui
{

ObjectInt::ObjectInt(std::string id, Object* parent)
    : Object("Int", id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace gui
