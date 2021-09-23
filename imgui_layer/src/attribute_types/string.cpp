#include "ilpch.h"
#include "attribute_types/string.h"

namespace gui
{

bool String::LoadValue(std::string value)
{
    this->value = value;
    return true;
}

std::string String::ToString()
{
    return this->value;
}

}  // namespace gui
