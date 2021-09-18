#include "ilpch.h"
#include "attribute_types/float4.h"

namespace gui
{

bool Float4::LoadValue(const char* value)
{
    std::vector<std::string> segments = utility::SplitString(value, ',');

    if (segments.size() != 4)
        return false;

    // X:
    if (!utility::StringToFloat(segments[0].c_str(), &this->x))
        return false;

    // Y:
    if (!utility::StringToFloat(segments[1].c_str(), &this->y))
    {
        this->x = 0.0f;
        return false;
    }

    // z:
    if (!utility::StringToFloat(segments[2].c_str(), &this->z))
    {
        this->x = 0.0f;
        this->y = 0.0f;
        return false;
    }

    // w:
    if (!utility::StringToFloat(segments[3].c_str(), &this->w))
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        return false;
    }

    return true;
}

}  // namespace gui
