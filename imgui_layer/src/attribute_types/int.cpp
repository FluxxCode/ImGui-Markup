#include "ilpch.h"
#include "attribute_types/int.h"

namespace gui
{

Int::Int()
{ }

Int::Int(int i)
    : value(i)
{ }

bool Int::LoadValue(std::string value)
{
    return utils::StringToInt(value, &this->value);
}

std::string Int::ToString()
{
    return std::to_string(this->value);
}

Int::operator int()
{
    return this->value;
}

std::ostream& operator<<(std::ostream& os, Int const& x)
{
    return os << x.value;
}

}  // namespace gui
