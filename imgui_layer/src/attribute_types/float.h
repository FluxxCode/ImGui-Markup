#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "attribute_types/attribute_type.h"

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

    void operator=(const float& x);

private:
    // Functions
    bool IMPLLoadValue(std::string value);

};

std::ostream& operator<<(std::ostream& os, Float const& x);

}

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
