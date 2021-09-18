#include "ilpch.h"
#include "attribute_types/float2.h"

namespace gui
{

bool Float2::LoadValue(const char* value)
{
     std::vector<std::string> segments = utility::SplitString(value, ',');

    if (segments.size() != 2)
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

    return true;
}

}  // namespace gui
