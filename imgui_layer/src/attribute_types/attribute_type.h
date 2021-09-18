#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

namespace gui
{

class AttributeType
{
public:
    // Functions
    virtual bool LoadValue(const char* value) = 0;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
