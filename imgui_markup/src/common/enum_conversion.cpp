#include "impch.h"
#include "common/enum_conversion.h"

namespace imgui_markup::internal::enums
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

}  // namespace imgui_markup::internal::enums
