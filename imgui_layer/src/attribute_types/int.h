#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Int : public AttributeType
{
public:
    bool LoadValue(std::string value);
    std::string ToString();
    int value_ = 0;
};

}  // namespace gui

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
