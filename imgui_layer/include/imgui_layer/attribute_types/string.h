#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_

#include "imgui_layer/attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class String : public Attribute
{
public:
    String();
    String(std::string str);
    String(const char* str);

    std::string value;

    std::string ToString() const;

    inline operator std::string() const { return value; }
    inline operator const char*() const { return value.c_str(); }

private:
    bool IMPL_LoadValue(const String& value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
