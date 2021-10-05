#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Float4 : public AttributeType
{
public:
    Float4();
    Float4(float x, float y, float z, float w);
    Float4(ImVec4 vec);

    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    std::string ToString();

    operator ImVec4();

private:
    // Functions
    bool IMPLLoadValue(std::string value);

    void SetError(std::string value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
