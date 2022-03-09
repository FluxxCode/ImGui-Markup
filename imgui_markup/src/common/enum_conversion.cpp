#include "impch.h"
#include "common/enum_conversion.h"

namespace imgui_markup::internal::enums
{

// LineAlignment
std::string GetEnumName(LineAlignment)
{
    return "LineAlignment";
}

bool ConvertEnum(std::string value, LineAlignment& out)
{
    if (value == "Left")
        out = LineAlignment::kLeft;
    else if (value == "Center")
        out = LineAlignment::kCenter;
    else if (value == "Right")
        out = LineAlignment::kRight;
    else
        return false;

    return true;
}

bool ConvertEnum(LineAlignment value, std::string& out)
{
    switch (value)
    {
    case LineAlignment::kLeft:   out = "Left";   break;
    case LineAlignment::kCenter: out = "Center"; break;
    case LineAlignment::kRight:  out = "Right";  break;
    default: return false;
    }

    return true;
}

}  // namespace imgui_markup::internal::enums
