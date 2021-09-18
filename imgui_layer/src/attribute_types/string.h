#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_

#include "attribute_types/attribute_type.h"

#include <string>

namespace gui
{

struct String : public AttributeType
{
    bool LoadValue(const char* value);
    std::string value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_STRING_H_
