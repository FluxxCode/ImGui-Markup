#include "ilpch.h"
#include "imgui_layer/attribute_types/int.h"

namespace gui
{

Int::Int()
    : Attribute(AttributeType::kInt)
{ }

Int::Int(int i)
    : Attribute(AttributeType::kInt), value(i)
{ }

std::string Int::ToString() const
{
    return std::to_string(this->value);
}

bool Int::IMPL_LoadValue(const Int& value_in)
{
    this->value = value_in;
    return true;
}

bool Int::IMPL_LoadValue(const String& value_in)
{
    return internal::utils::StringToInt(value_in, &this->value);
}

}  // namespace gui
