#include "ilpch.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{
String::String()
{ }

String::String(std::string str)
    : value(str)
{ }

String::String(const char* str)
    : value(str)
{ }

std::string String::ToString() const
{
    return this->value;
}

String::operator std::string()
{
    return this->value;
}

String::operator const char* ()
{
    return this->value.c_str();
}

bool String::IMPLLoadValue(std::string value)
{
    this->value = value;
    return true;
}

std::ostream& operator<<(std::ostream& os, String const& str)
{
    return os << str.value;
}

}  // namespace gui
