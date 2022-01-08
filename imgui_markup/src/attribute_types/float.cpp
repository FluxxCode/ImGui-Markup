#include "impch.h"
#include "imgui_markup/attribute_types/float.h"

namespace imgui_markup
{

Float::Float()
    : Attribute(AttributeType::kFloat)
{ }

Float::Float(float f)
    : Attribute(AttributeType::kFloat), value(f)
{ }

std::string Float::ToString() const
{
    return std::to_string(this->value);
}

bool Float::IMPL_LoadValue(const Float& value_in)
{
    this->value = value_in;
    return true;
}

bool Float::IMPL_LoadValue(const String& value_in)
{
    return internal::utils::StringToFloat(value_in, &this->value);
}

}  // namespace imgui_markup
