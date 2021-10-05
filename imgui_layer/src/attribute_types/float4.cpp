#include "ilpch.h"
#include "attribute_types/float4.h"

namespace gui
{

Float4::Float4()
{ }

Float4::Float4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
{ }

Float4::Float4(ImVec4 vec)
    : x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{ }

std::string Float4::ToString()
{
    return std::to_string(this->x) + "," +
        std::to_string(this->y) + "," +
        std::to_string(this->z) + "," +
        std::to_string(this->w);
}

Float4::operator ImVec4()
{
    return ImVec4(this->x, this->y, this->z, this->w);
}

bool Float4::IMPLLoadValue(std::string value)
{
    std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 4)
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
    {
        this->SetError(value);
        return false;
    }

    // z:
    if (!utils::StringToFloat(segments[2].c_str(), &this->z))
    {
        this->SetError(value);
        return false;
    }

    // w:
    if (!utils::StringToFloat(segments[3].c_str(), &this->w))
    {
        this->SetError(value);
        return false;
    }

    return true;
}

void Float4::SetError(std::string value)
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;

    this->last_error_ = ParserError(ParserErrorType::kConversionError,
        "Unable to convert \"" + value + "\" to a float4");
}

}  // namespace gui
