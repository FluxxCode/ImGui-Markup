#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_

#include "objects/common/object.h"
#include "attribute_types/float3.h"

namespace imgui_markup
{

struct ObjectFloat3 : public Object
{
    ObjectFloat3(std::string id, Object* parent);

    ObjectFloat3& operator=(const ObjectFloat3& other);

    Float3 value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
