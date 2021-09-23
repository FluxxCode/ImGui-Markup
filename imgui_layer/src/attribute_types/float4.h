#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct Float4 : public AttributeType
{
    bool LoadValue(std::string value);
    std::string ToString();
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
