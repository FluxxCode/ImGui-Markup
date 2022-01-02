#include "ilpch.h"
#include "imgui_layer/attribute_types/float2.h"

namespace gui
{

Float2::Float2()
    : Attribute(AttributeType::kFloat2)
{ }

Float2::Float2(float x, float y)
    : Attribute(AttributeType::kFloat2), x(x), y(y)
{ }

Float2::Float2(ImVec2 vec)
    : Attribute(AttributeType::kFloat2), x(vec.x), y(vec.y)
{ }

std::string Float2::ToString() const
{
    return std::to_string(this->x) + ", " + std::to_string(this->y);
}

bool Float2::IMPL_LoadValue(std::string value_in)
{
    std::vector<std::string> segments = utils::SplitString(value_in, ',');

    if (segments.size() != 2)
        return false;

    if (!this->x.LoadValue(segments[0]))
        return false;

    // Y:
    if (!this->y.LoadValue(segments[1]))
        return false;

    return true;
}

}  // namespace gui
