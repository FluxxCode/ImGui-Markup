#include "impch.h"
#include "attribute_types/attribute_type.h"

namespace imgui_markup
{

Attribute::Attribute(AttributeType type)
    : type(type)
{ }

bool Attribute::LoadValue(const Attribute& value)
{
    switch (value.type)
    {
    case AttributeType::kBool:   return this->LoadValue<Bool>((Bool&)value);
    case AttributeType::kFloat:  return this->LoadValue<Float>((Float&)value);
    case AttributeType::kFloat2: return this->LoadValue<Float2>((Float2&)value);
    case AttributeType::kFloat3: return this->LoadValue<Float3>((Float3&)value);
    case AttributeType::kFloat4: return this->LoadValue<Float4>((Float4&)value);
    case AttributeType::kInt:    return this->LoadValue<Int>((Int&)value);
    case AttributeType::kString: return this->LoadValue<String>((String&)value);
    default: return false;
    }
}

bool Attribute::LoadValue(const Bool& value_in)
{
    return this->LoadValue<Bool>(value_in);
}

bool Attribute::LoadValue(const Float& value_in)
{
    return this->LoadValue<Float>(value_in);
}

bool Attribute::LoadValue(const Float2& value_in)
{
    return this->LoadValue<Float2>(value_in);
}

bool Attribute::LoadValue(const Float3& value_in)
{
    return this->LoadValue<Float3>(value_in);
}

bool Attribute::LoadValue(const Float4& value_in)
{
    return this->LoadValue<Float4>(value_in);
}

bool Attribute::LoadValue(const Int& value_in)
{
    return this->LoadValue<Int>(value_in);
}

bool Attribute::LoadValue(const String& value_in)
{
    return this->LoadValue<String>(value_in);
}

}  // namespace imgui_markup
