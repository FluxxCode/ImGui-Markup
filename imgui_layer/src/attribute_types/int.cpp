#include "ilpch.h"
#include "attribute_types/int.h"

namespace gui
{

bool Int::LoadValue(std::string value)
{
    return utility::StringToInt(value, &this->value_);
}

std::string Int::ToString()
{
    return std::to_string(this->value_);
}

}  // namespace gui
