#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/float2.h"

namespace imgui_markup
{

struct ObjectFloat2 : public Object
{
    ObjectFloat2(std::string id, Object* parent);

    ObjectFloat2& operator=(const ObjectFloat2& other);

    Float2 value;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
