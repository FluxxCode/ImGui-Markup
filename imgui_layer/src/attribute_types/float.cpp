#include "ilpch.h"
#include "imgui_layer/attribute_types/float.h"

namespace gui
{

Float::Float()
{ }

Float::Float(float f)
    : value(f)
{ }

std::string Float::ToString()
{
    return std::to_string(this->value);
}

Float::operator float()
{
    return this->value;
}

bool Float::IMPLLoadValue(std::string value)
{
    if (!utils::StringToFloat(value, &this->value))
    {
        this->last_error_ = ParserError(ParserErrorType::kConversionError,
            "Unable to convert \"" + value + "\" to a float");

        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, Float const& x)
{
    return os << x.value;
}

}  // namespace gui
