#include "impch.h"
#include "attribute_types/float3.h"

namespace imgui_markup::internal
{

Float3::Float3()
    : AttributeBase(AttributeType::kFloat3)
{ }

Float3::Float3(float x, float y, float z)
    : AttributeBase(AttributeType::kFloat3), x(x), y(y), z(z)
{ }

std::string Float3::ToString() const
{
    return std::to_string(this->x) + "," +
           std::to_string(this->y) + "," +
           std::to_string(this->z);
}

bool Float3::IMPL_LoadValue(const Float3& value_in)
{
    this->x = value_in.x;
    this->y = value_in.y;
    this->z = value_in.z;
    return true;
}

bool Float3::IMPL_LoadValue(const String& value_in)
{
    std::vector<std::string> segments =
        internal::utils::SplitString(value_in, ',');

    if (segments.size() != 3)
        return false;

    // X:
    if (!this->x.LoadValue(String(segments[0])))
        return false;

    // Y:
    if (!this->y.LoadValue(String(segments[1])))
        return false;

    // z:
    if (!this->z.LoadValue(String(segments[2])))
        return false;

    return true;
}

}  // namespace imgui_markup::internal
