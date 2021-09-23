#include "ilpch.h"
#include "attribute_types/bool.h"

namespace gui
{

bool Bool::LoadValue(std::string value)
{
    return utility::StringToBool(value, &this->value);
}

std::string Bool::ToString()
{
    return utility::BoolToString(this->value);
}

}  // namespace gui
