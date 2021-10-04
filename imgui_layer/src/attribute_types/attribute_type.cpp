#include "ilpch.h"
#include "attribute_types/attribute_type.h"

namespace gui
{

bool AttributeType::LoadValue(std::string value)
{
    if (!this->IMPLLoadValue(value))
        return false;

    this->value_changed_ = true;
    return true;
}

}  // namespace gui
