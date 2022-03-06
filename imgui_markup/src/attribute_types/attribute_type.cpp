#include "impch.h"
#include "attribute_types/attribute_type.h"

#include "attribute_types/reference.h"

namespace imgui_markup::internal
{

Attribute::Attribute(AttributeType type)
    : type(type)
{ }

Attribute::~Attribute()
{
    // Set references pointing to this attribute to nullptr
    for (Reference* reference : this->references_)
        reference->reference = nullptr;
}

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
    case AttributeType::kReference:
        return this->LoadValue<Reference>((Reference&)value);
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

bool Attribute::LoadValue(const Reference& value_in)
{
    return this->LoadValue<Reference>(value_in);
}

void Attribute::InitReference(Reference* reference)
{
    this->references_.push_back(reference);
}

void Attribute::RemoveReference(Reference* reference)
{
    for (unsigned int i = 0; i < this->references_.size(); i++)
    {
        if (this->references_[i] == reference)
            this->references_.erase(this->references_.begin() + i);
    }
}

bool Attribute::IMPL_LoadValue(const Reference& value)
{
    if (!value.reference)
        return false;

    return this->LoadValue(*value.reference);
}

}  // namespace imgui_markup::internal
