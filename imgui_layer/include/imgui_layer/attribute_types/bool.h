#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_

#include "imgui_layer/attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class Bool : public Attribute
{
public:
    Bool();
    Bool(const bool b);

    bool value = true;

    std::string ToString() const;

    inline operator bool() const { return value; }

private:
    bool IMPL_LoadValue(std::string value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
