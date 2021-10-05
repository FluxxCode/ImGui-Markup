#include "ilpch.h"
#include "attribute_types/float2.h"

namespace gui
{
Float2::Float2()
{ }

Float2::Float2(float x, float y)
    : x(x), y(y)
{ }

Float2::Float2(ImVec2 vec)
    : x(vec.x), y(vec.y)
{ }

std::string Float2::ToString()
{
    return std::to_string(this->x) + ", " + std::to_string(this->y);
}

Float2::operator ImVec2()
{
    return ImVec2(this->x, this->y);
}

bool Float2::IMPLLoadValue(std::string value)
{
    std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 2)
    {
        this->SetError(value);
        return false;
    }

    // X:
    if (!utils::StringToFloat(segments[0].c_str(), &this->x))
    {
        this->SetError(value);
        return false;
    }

    // Y:
    if (!utils::StringToFloat(segments[1].c_str(), &this->y))
        this->SetError(value);


    return true;
}

void Float2::SetError(std::string value)
{
    this->x = 0;
    this->y = 0;

    this->last_error_ = ParserError(ParserErrorType::kConversionError,
        "Unable to convert \"" + value + "\" to a float2");
}

}  // namespace gui
