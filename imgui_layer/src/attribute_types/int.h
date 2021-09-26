#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct Int : public AttributeType
{
    Int();
    Int(int i);

    int value = 0;

    bool LoadValue(std::string value);
    std::string ToString();

    operator int();
};

std::ostream& operator<<(std::ostream& os, Int const& x);

}  // namespace gui

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
