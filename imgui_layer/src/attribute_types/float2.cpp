#include "ilpch.h"
#include "imgui_layer/attribute_types/float2.h"

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

AttributeType* Float2::GetChild(std::string name)
{
    if (name == "x")
        return &this->x;
    if (name == "y")
        return &this->y;

    return nullptr;
}

bool Float2::HasChild(std::string name)
{
    if (name == "x" || name == "y")
        return true;

    return false;
}

std::string Float2::ToString()
{
    return std::to_string(this->x) + ", " + std::to_string(this->y);
}

Float2::operator ImVec2()
{
    return ImVec2(this->x, this->y);
}

bool Float2::IMPLLoadValue(std::string value)
{
    std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 2)
    {
        this->SetError(value);
        return false;
    }

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


    return true;
}

void Float2::SetError(std::string value)
{
    // TODO: Migrate to the new parser system

    //this->last_error_ = ParserError(ParserErrorType::kConversionError,
    //    "Unable to convert \"" + value + "\" to a float2");

    this->ResetValues();

}

void Float2::SetError(std::string value, Float& child)
{
    // TODO: Migrate to the new parser system

    //this->last_error_ = child.GetLastError();
    //this->last_error_.message_ =
    //    "Unable to convert \"" + value + "\" to a float2: " +
    //    this->last_error_.message_;

    this->ResetValues();
}

void Float2::ResetValues()
{
    this->x = 0;
    this->y = 0;
}

}  // namespace gui
