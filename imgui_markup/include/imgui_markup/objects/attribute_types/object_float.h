#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/float.h"

namespace imgui_markup
{

struct ObjectFloat : public Object
{
    ObjectFloat(std::string id, Object* parent);

    ObjectFloat& operator=(const ObjectFloat& other);

    Float value;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
