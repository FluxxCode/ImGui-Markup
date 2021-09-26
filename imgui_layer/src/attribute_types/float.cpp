#include "ilpch.h"
#include "attribute_types/float.h"

namespace gui
{

Float::Float()
{ }

Float::Float(float f)
    : value(f)
{ }

bool Float::LoadValue(std::string value)
{
    return utility::StringToFloat(value, &this->value);
}

std::string Float::ToString()
{
    return std::to_string(this->value);
}

void Float::operator=(const float& x)
{
    this->value = x;
}

std::ostream& operator<<(std::ostream& os, Float const& x)
{
    return os << x.value;
}

}  // namespace gui
