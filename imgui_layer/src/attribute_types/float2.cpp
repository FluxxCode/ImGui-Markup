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

bool Float2::LoadValue(std::string value)
{
     std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 2)
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

    return true;
}

std::string Float2::ToString()
{
    return std::to_string(this->x) + ", " + std::to_string(this->y);
}

Float2::operator ImVec2()
{
    return ImVec2(this->x, this->y);
}

}  // namespace gui
