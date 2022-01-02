#include "ilpch.h"
#include "imgui_layer/attribute_types/float3.h"

namespace gui
{

Float3::Float3()
    : Attribute(AttributeType::kFloat3)
{ }

Float3::Float3(float x, float y, float z)
    : Attribute(AttributeType::kFloat3), x(x), y(y), z(z)
{ }

std::string Float3::ToString() const
{
    return std::to_string(this->x) + "," +
           std::to_string(this->y) + "," +
           std::to_string(this->z);
}

bool Float3::IMPL_LoadValue(std::string value_in)
{
    std::vector<std::string> segments = utils::SplitString(value_in, ',');

    if (segments.size() != 3)
        return false;

    // X:
    if (!this->x.LoadValue(segments[0]))
        return false;

    // Y:
    if (!this->y.LoadValue(segments[1]))
        return false;

    // z:
    if (!this->z.LoadValue(segments[2]))
        return false;

    return true;
}

}  // namespace gui
