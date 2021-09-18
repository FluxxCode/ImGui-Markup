#include "ilpch.h"
#include "attribute_types/bool.h"

namespace gui
{

bool Bool::LoadValue(const char* value)
{
    return utility::StringToBool(value, &this->value);
}

}  // namespace gui
