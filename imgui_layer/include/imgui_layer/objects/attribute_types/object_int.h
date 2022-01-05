#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/int.h"

namespace gui
{

struct ObjectInt : public Object
{
    ObjectInt(std::string id, Object* parent);

    ObjectInt& operator=(const ObjectInt& other);

    Int value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
