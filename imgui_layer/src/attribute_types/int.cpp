#include "ilpch.h"
#include "imgui_layer/attribute_types/int.h"

namespace gui
{

Int::Int()
{ }

Int::Int(int i)
    : value(i)
{ }

std::string Int::ToString() const
{
    return std::to_string(this->value);
}

Int::operator int()
{
    return this->value;
}

bool Int::IMPLLoadValue(std::string value)
{
    if (!utils::StringToInt(value, &this->value))
    {
        // TODO: Migrate to the new parser system

        //this->last_error_ = ParserError(ParserErrorType::kConversionError,
        //    "Unable to convert \"" + value + "\" to an int");

        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, Int const& x)
{
    return os << x.value;
}

}  // namespace gui
