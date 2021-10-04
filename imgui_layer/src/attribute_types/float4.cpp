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
        return false;

    // X:
    if (!utils::StringToFloat(segments[0].c_str(), &this->x))
        return false;

    // Y:
    if (!utils::StringToFloat(segments[1].c_str(), &this->y))
    {
        this->x = 0.0f;
        return false;
    }

    // z:
    if (!utils::StringToFloat(segments[2].c_str(), &this->z))
    {
        this->x = 0.0f;
        this->y = 0.0f;
        return false;
    }

    // w:
    if (!utils::StringToFloat(segments[3].c_str(), &this->w))
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        return false;
    }

    return true;
}

}  // namespace gui
