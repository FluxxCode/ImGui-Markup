#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_

#include "imgui_layer/attribute_types/attribute_type.h"

namespace gui
{

class Bool : public AttributeType
{
public:
    Bool();
    Bool(const bool b);

    bool value = true;

    std::string ToString();

    void operator=(const bool& x);

private:
    // Functions
    bool IMPLLoadValue(std::string value);
};

std::ostream& operator<<(std::ostream& os, Bool& x);

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
