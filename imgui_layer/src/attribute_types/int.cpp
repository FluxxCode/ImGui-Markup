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

bool Int::IMPL_LoadValue(std::string value_in)
{
    return utils::StringToInt(value_in, &this->value);
}

}  // namespace gui
