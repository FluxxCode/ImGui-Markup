#include "ilpch.h"
#include "attribute_types/string.h"

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

bool String::LoadValue(std::string value)
{
    this->value = value;
    return true;
}

std::string String::ToString()
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

std::ostream& operator<<(std::ostream& os, String const& str)
{
    return os << str.value;
}

}  // namespace gui
