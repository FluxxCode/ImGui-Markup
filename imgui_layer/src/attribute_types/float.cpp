#include "ilpch.h"
#include "attribute_types/float.h"

namespace gui
{

bool Float::LoadValue(std::string value)
{
    return utility::StringToFloat(value, &this->value);
}

std::string Float::ToString()
{
    return std::to_string(this->value);
}

}  // namespace gui
