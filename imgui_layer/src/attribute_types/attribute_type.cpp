#include "ilpch.h"
#include "imgui_layer/attribute_types/attribute_type.h"

namespace gui
{

bool AttributeType::LoadValue(std::string value)
{
    if (!this->IMPLLoadValue(value))
        return false;

    this->value_changed_ = true;
    return true;
}

AttributeType* AttributeType::GetChild(std::string id)
{
    return nullptr;
}

bool AttributeType::HasChild(std::string id)
{
    return false;
}

ParserError AttributeType::GetLastError() const
{
    return this->last_error_;
}

}  // namespace gui
