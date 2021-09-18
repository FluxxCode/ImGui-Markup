#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_

#include "attribute_types/attribute_type.h"

namespace gui
{

struct Float2 : public AttributeType
{
    bool LoadValue(const char* value);
    float x = 0;
    float y = 0;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
