#include "ilpch.h"
#include "attribute_types/int.h"

namespace gui
{

bool Int::LoadValue(const char* value)
{
    return utility::StringToInt(value, &this->value_);
}

}  // namespace gui
