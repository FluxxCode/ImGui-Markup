#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
{

struct ObjectString : public Object
{
    ObjectString(std::string id, Object* parent);

    ObjectString& operator=(const ObjectString& other);

    String value;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
