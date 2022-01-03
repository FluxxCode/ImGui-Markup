#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/float.h"

namespace gui
{

struct ObjectFloat : public Object
{
    ObjectFloat(std::string id, Object* parent);

    Float value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
