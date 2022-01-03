#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/float2.h"

namespace gui
{

struct ObjectFloat2 : public Object
{
    ObjectFloat2(std::string id, Object* parent);

    Float2 value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
