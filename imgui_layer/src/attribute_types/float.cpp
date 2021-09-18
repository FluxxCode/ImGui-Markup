#include "ilpch.h"
#include "attribute_types/float.h"

namespace gui
{

bool Float::LoadValue(const char* value)
{
    return utility::StringToFloat(value, &this->value);
}

}  // namespace gui
