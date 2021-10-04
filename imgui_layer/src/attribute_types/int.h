#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Int : public AttributeType
{
public:
    Int();
    Int(int i);

    int value = 0;

    std::string ToString();

    operator int();

private:
    // Functions
    bool IMPLLoadValue(std::string value);
};

std::ostream& operator<<(std::ostream& os, Int const& x);

}  // namespace gui

#endif IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
