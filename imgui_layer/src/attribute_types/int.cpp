#include "ilpch.h"
#include "attribute_types/int.h"

namespace gui
{

Int::Int()
{ }

Int::Int(int i)
    : value(i)
{ }

std::string Int::ToString()
{
    return std::to_string(this->value);
}

Int::operator int()
{
    return this->value;
}

bool Int::IMPLLoadValue(std::string value)
{
    return utils::StringToInt(value, &this->value);
}

std::ostream& operator<<(std::ostream& os, Int const& x)
{
    return os << x.value;
}

}  // namespace gui
