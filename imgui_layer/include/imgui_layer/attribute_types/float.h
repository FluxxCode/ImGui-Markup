#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "imgui_layer/attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Float : public AttributeType
{
public:
    Float();
    Float(float f);

    float value = 0;

    std::string ToString();

    operator float();

private:
    // Functions
    bool IMPLLoadValue(std::string value);

};

std::ostream& operator<<(std::ostream& os, Float const& x);

}

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
