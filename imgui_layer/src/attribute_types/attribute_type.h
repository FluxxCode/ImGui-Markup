#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include <string>

namespace gui
{

class AttributeType
{
public:
    // Functions
    virtual bool LoadValue(std::string value) = 0;
    virtual std::string ToString() = 0;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
