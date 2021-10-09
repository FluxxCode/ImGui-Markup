#include "ilpch.h"
#include "attribute_types/float4.h"
#include "float4.h"

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

AttributeType* Float4::GetChild(std::string name)
{
    if (name == "x")
        return &this->x;
    if (name == "y")
        return &this->y;
    if (name == "z")
        return &this->z;
    if (name == "w")
        return &this->w;

    return nullptr;
}

bool Float4::HasChild(std::string name)
{
    if (name == "x" || name == "y" || name == "z" || name == "w")
        return true;

    return false;
}

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
    if (!this->x.LoadValue(segments[0]))
    {
        this->SetError(value, this->x);
        return false;
    }

    // Y:
    if (!this->y.LoadValue(segments[1]))
    {
        this->SetError(value, this->y);
        return false;
    }

    // z:
    if (!this->z.LoadValue(segments[2]))
    {
        this->SetError(value, this->z);
        return false;
    }

    // w:
    if (!this->w.LoadValue(segments[3]))
    {
        this->SetError(value, this->w);
        return false;
    }

    return true;
}

void Float4::SetError(std::string value)
{
    this->last_error_ = ParserError(ParserErrorType::kConversionError,
        "Unable to convert \"" + value + "\" to a float4");

    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

void Float4::SetError(std::string value, Float& child)
{
    this->last_error_ = child.GetLastError();
    this->last_error_.message_ =
        "Unable to convert \"" + value + "\" to a float4: " +
        this->last_error_.message_;

    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

}  // namespace gui
