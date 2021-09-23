#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct Float : public AttributeType
{
    bool LoadValue(std::string value);
    std::string ToString();
    float value = 0;
};

}

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
