#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "attribute_types/attribute_type.h"

namespace gui
{

struct Float : public AttributeType
{
    bool LoadValue(const char* value);
    float value = 0;
};

}

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
