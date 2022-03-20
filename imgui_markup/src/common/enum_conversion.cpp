#include "impch.h"
#include "common/enum_conversion.h"

namespace igm::internal::enums
{

// LineAlignment
std::string GetEnumName(Alignment)
{
    return "Alignment";
}

bool ConvertEnum(std::string value, Alignment& out)
{
    if (value == "Left")
        out = Alignment::kLeft;
    else if (value == "Center")
        out = Alignment::kCenter;
    else if (value == "Right")
        out = Alignment::kRight;
    else
        return false;

    return true;
}

bool ConvertEnum(Alignment value, std::string& out)
{
    switch (value)
    {
    case Alignment::kLeft:   out = "Left";   break;
    case Alignment::kCenter: out = "Center"; break;
    case Alignment::kRight:  out = "Right";  break;
    default: return false;
    }

    return true;
}

// Orientation
std::string GetEnumName(Orientation)
{
    return "Orientation";
}

bool ConvertEnum(std::string value, Orientation& out)
{
    if (value == "Vertical")
        out = Orientation::kVertical;
    else if (value == "Horizontal")
        out = Orientation::kHorizontal;
    else
        return false;

    return true;
}

bool ConvertEnum(Orientation value, std::string& out)
{
    switch (value)
    {
    case Orientation::kVertical:   out = "Vertical";   break;
    case Orientation::kHorizontal: out = "Horizontal"; break;
    default: return false;
    }

    return true;
}

}  // namespace igm::internal::enums
