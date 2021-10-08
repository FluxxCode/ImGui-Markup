#include "ilpch.h"
#include "attribute_types/float3.h"

namespace gui
{

Float3::Float3()
{ }

Float3::Float3(float x, float y, float z)
    : x(x), y(y), z(z)
{ }

std::string Float3::ToString()
{
    return std::to_string(this->x) + "," +
           std::to_string(this->y) + "," +
           std::to_string(this->z);
}

bool Float3::IMPLLoadValue(std::string value)
{
    std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 3)
    {
        this->SetError(value);
        return false;
    }

    // X:
    if (!this->x.LoadValue(segments[0]))
    {
        this->SetError(this->x.GetLastError().message_);
        return false;
    }

    // Y:
    if (!this->y.LoadValue(segments[1]))
    {
        this->SetError(this->y.GetLastError().message_);
        return false;
    }

    // z:
    if (!this->z.LoadValue(segments[2]))
    {
        this->SetError(this->z.GetLastError().message_);
        return false;
    }

    return true;
}

void Float3::SetError(std::string value)
{
    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->last_error_ = ParserError(ParserErrorType::kConversionError,
        "Unable to convert \"" + value + "\" to a float3");
}

}  // namespace gui
