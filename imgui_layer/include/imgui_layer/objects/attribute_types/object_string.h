#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{

struct ObjectString : public Object
{
    ObjectString(std::string id, Object* parent);

    String value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
