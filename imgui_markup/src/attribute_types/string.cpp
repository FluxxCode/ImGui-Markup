#include "impch.h"
#include "attribute_types/string.h"

#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float3.h"
#include "attribute_types/float4.h"
#include "attribute_types/int.h"
#include "attribute_types/string.h"

namespace igm::internal
{

String::String()
    : AttributeBase(AttributeType::kString)
{ }

String::String(std::string str)
    : AttributeBase(AttributeType::kString), value(str)
{ }

String::String(const char* str)
    : AttributeBase(AttributeType::kString), value(str)
{ }

std::string String::ToString() const
{
    return this->value;
}

bool String::IMPL_LoadValue(const Bool& value_in)
{
    this->value = value_in.ToString();
    return true;
}

bool String::IMPL_LoadValue(const Float& value_in)
{
    this->value = value_in.ToString();
    return true;
}

bool String::IMPL_LoadValue(const Float2& value_in)
{
    this->value = value_in.ToString();
    return true;
}

bool String::IMPL_LoadValue(const Float3& value_in)
{
    this->value = value_in.ToString();
    return true;
}


bool String::IMPL_LoadValue(const Float4& value_in)
{
    this->value = value_in.ToString();
    return true;
}


bool String::IMPL_LoadValue(const Int& value_in)
{
    this->value = value_in.ToString();
    return true;
}

bool String::IMPL_LoadValue(const String& value_in)
{
    this->value = value_in.value;
    return true;
}

}  // namespace igm::internal
