#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/attribute_types/float4.h"

namespace gui
{

struct ObjectFloat4 : public Object
{
    ObjectFloat4(std::string id, Object* parent);

    ObjectFloat4& operator=(const ObjectFloat4& other);

    Float4 value;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
