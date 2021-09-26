#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_

#include "attribute_types/attribute_type.h"

namespace gui
{

struct Bool : public AttributeType
{
    Bool();
    Bool(const bool b);

    bool value = true;

    bool LoadValue(std::string value);
    std::string ToString();

    void operator=(const bool& x);
};

std::ostream& operator<<(std::ostream& os, Bool& x);

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
