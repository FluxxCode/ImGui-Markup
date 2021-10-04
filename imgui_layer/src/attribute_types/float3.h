#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Float3 : public AttributeType
{
public:
    Float3();
    Float3(float x, float y, float z);

    float x = 0;
    float y = 0;
    float z = 0;

    std::string ToString();

private:
    // Functions
    bool IMPLLoadValue(std::string value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_
