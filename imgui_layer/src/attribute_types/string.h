#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct String : public AttributeType
{
    String();
    String(std::string str);
    String(const char* str);

    std::string value;

    bool LoadValue(std::string value);
    std::string ToString();

    operator std::string();
    operator const char*();
};

std::ostream& operator<<(std::ostream& os, String const& str);

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
