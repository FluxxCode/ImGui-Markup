#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_

#include "attribute_types/attribute_type.h"

namespace gui
{

class Int : public AttributeType
{
public:
    bool LoadValue(const char* value);
    int value_ = 0;
};

}  // namespace gui

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
