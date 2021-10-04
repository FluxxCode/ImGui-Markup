#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include <string>

namespace gui
{

struct AttributeType
{
    // Functions
    bool LoadValue(std::string value);
    virtual bool IMPLLoadValue(std::string value) = 0;

    virtual std::string ToString() = 0;

    bool value_changed_ = false;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
