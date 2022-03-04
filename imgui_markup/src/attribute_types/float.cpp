#include "impch.h"
#include "attribute_types/float.h"

namespace imgui_markup::internal
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

bool Float::IMPL_LoadValue(const Int& value_in)
{
    this->value = value_in.value;
    return true;
}

}  // namespace imgui_markup::internal
