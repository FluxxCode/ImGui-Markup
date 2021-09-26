#include "ilpch.h"
#include "attribute_types/bool.h"

namespace gui
{

Bool::Bool()
{ }

Bool::Bool(const bool b)
    : value(b)
{ }

bool Bool::LoadValue(std::string value)
{
    return utility::StringToBool(value, &this->value);
}

std::string Bool::ToString()
{
    return utility::BoolToString(this->value);
}

void Bool::operator=(const bool& x)
{
    this->value = x;
}

std::ostream& operator<<(std::ostream& os, Bool& x)
{
    return os << x.value;
}

}  // namespace gui
