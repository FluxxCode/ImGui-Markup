#include "ilpch.h"
#include "imgui_layer/attribute_types/bool.h"

namespace gui
{

Bool::Bool()
    : Attribute(AttributeType::kBool)
{ }

Bool::Bool(const bool b)
    : Attribute(AttributeType::kBool), value(b)
{ }

std::string Bool::ToString() const
{
    return utils::BoolToString(this->value);
}

bool Bool::IMPL_LoadValue(std::string value_in)
{
    return utils::StringToBool(value_in, &this->value);
}

}  // namespace gui
