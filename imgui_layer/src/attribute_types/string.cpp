#include "ilpch.h"
#include "attribute_types/string.h"

namespace gui
{

bool String::LoadValue(const char* value)
{
    this->value = value;
    return true;
}

}  // namespace gui
