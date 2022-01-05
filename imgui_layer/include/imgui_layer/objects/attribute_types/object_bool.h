#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/bool.h"

namespace gui
{

struct ObjectBool : public Object
{
    ObjectBool(std::string id, Object* parent);

    ObjectBool& operator=(const ObjectBool& other);

    Bool value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
