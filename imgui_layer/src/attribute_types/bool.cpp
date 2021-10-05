#include "ilpch.h"
#include "attribute_types/bool.h"

namespace gui
{

Bool::Bool()
{ }

Bool::Bool(const bool b)
    : value(b)
{ }

std::string Bool::ToString()
{
    return utils::BoolToString(this->value);
}

void Bool::operator=(const bool& x)
{
    this->value = x;
}

bool Bool::IMPLLoadValue(std::string value)
{
    if (!utils::StringToBool(value, &this->value))
    {
        this->last_error_ = ParserError(ParserErrorType::kConversionError,
            "Unable to convert \"" + value + "\" to a bool");

        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, Bool& x)
{
    return os << x.value;
}

}  // namespace gui
