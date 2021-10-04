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

    return true;
}

}  // namespace gui
