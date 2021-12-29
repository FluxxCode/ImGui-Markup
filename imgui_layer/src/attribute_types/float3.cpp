#include "ilpch.h"
#include "imgui_layer/attribute_types/float3.h"

namespace gui
{

Float3::Float3()
{ }

Float3::Float3(float x, float y, float z)
    : x(x), y(y), z(z)
{ }

AttributeType* Float3::GetChild(std::string name)
{
    if (name == "x")
        return &this->x;
    if (name == "y")
        return &this->y;
    if (name == "z")
        return &this->z;

    return nullptr;
}

bool Float3::HasChild(std::string name)
{
    if (name == "x" || name == "y" || name == "z")
        return true;

    return false;
}

std::string Float3::ToString() const
{
    return std::to_string(this->x.value) + "," +
           std::to_string(this->y.value) + "," +
           std::to_string(this->z.value);
}

bool Float3::IMPLLoadValue(std::string value)
{
    std::vector<std::string> segments = utils::SplitString(value, ',');

    if (segments.size() != 3)
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

    return true;
}

void Float3::SetError(std::string value)
{
    // TODO: Migrate to the new parser system

    //this->last_error_ = ParserError(ParserErrorType::kConversionError,
    //    "Unable to convert \"" + value + "\" to a float3");

    this->ResetValues();
}

void Float3::SetError(std::string value, Float& child)
{
    // TODO: Migrate to the new parser system

    //this->last_error_ = child.GetLastError();
    //this->last_error_.message_ =
    //    "Unable to convert \"" + value + "\" to a float3: " +
    //    this->last_error_.message_;

    this->ResetValues();
}

void Float3::ResetValues()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

}  // namespace gui
