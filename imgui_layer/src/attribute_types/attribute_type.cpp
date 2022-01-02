#include "ilpch.h"
#include "imgui_layer/attribute_types/attribute_type.h"

namespace gui
{

Attribute::Attribute(AttributeType type)
    : type(type)
{ }

bool Attribute::LoadValue(std::string value)
{
    if (this->IMPL_LoadValue(value))
    {
        this->value_changed_ = true;
        return true;
    }

    return false;
}

}  // namespace gui
