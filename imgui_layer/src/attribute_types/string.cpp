#include "ilpch.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{

String::String()
    : Attribute(AttributeType::kString)
{ }

String::String(std::string str)
    : Attribute(AttributeType::kString), value(str)
{ }

String::String(const char* str)
    : Attribute(AttributeType::kString), value(str)
{ }

std::string String::ToString() const
{
    return this->value;
}

bool String::IMPL_LoadValue(std::string value_in)
{
    this->value = value_in;
    return true;
}

}  // namespace gui
