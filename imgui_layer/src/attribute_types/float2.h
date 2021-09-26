#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct Float2 : public AttributeType
{
    Float2();
    Float2(float x, float y);
    Float2(ImVec2 vec);

    float x = 0;
    float y = 0;

    bool LoadValue(std::string value);
    std::string ToString();

    operator ImVec2();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
