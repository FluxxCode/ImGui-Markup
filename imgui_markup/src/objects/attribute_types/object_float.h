#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_

#include "objects/common/object.h"
#include "attribute_types/float.h"

namespace imgui_markup::internal{

struct ObjectFloat : public Object
{
    ObjectFloat(std::string id, Object* parent);

    ObjectFloat& operator=(const ObjectFloat& other);

    Float value;
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
