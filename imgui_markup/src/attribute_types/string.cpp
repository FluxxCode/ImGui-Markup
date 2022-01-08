#include "impch.h"
#include "imgui_markup/attribute_types/string.h"

#include "imgui_markup/attribute_types/bool.h"
#include "imgui_markup/attribute_types/float.h"
#include "imgui_markup/attribute_types/float2.h"
#include "imgui_markup/attribute_types/float3.h"
#include "imgui_markup/attribute_types/float4.h"
#include "imgui_markup/attribute_types/int.h"
#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
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

}  // namespace imgui_markup
