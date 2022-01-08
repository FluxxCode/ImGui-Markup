#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/float3.h"

namespace imgui_markup
{

struct ObjectFloat3 : public Object
{
    ObjectFloat3(std::string id, Object* parent);

    ObjectFloat3& operator=(const ObjectFloat3& other);

    Float3 value;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
