#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Float2 : public AttributeType
{
public:
    Float2();
    Float2(float x, float y);
    Float2(ImVec2 vec);

    float x = 0;
    float y = 0;

    std::string ToString();

    operator ImVec2();

private:
    // Functions
    bool IMPLLoadValue(std::string value);

    void SetError(std::string value);

};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
