#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_

#include "imgui_layer/attribute_types/attribute_type.h"

#include <string>

namespace gui
{

class String : public AttributeType
{
public:
    String();
    String(std::string str);
    String(const char* str);

    std::string value;

    std::string ToString() const;

    operator std::string();
    operator const char*();

private:
    // Functions
    bool IMPLLoadValue(std::string value);
};

std::ostream& operator<<(std::ostream& os, String const& str);

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
