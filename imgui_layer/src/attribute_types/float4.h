#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct Float4 : public AttributeType
{
    Float4();
    Float4(float x, float y, float z, float w);
    Float4(ImVec4 vec);

    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    bool LoadValue(std::string value);
    std::string ToString();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
