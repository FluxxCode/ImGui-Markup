#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_

#include "objects/common/object.h"
#include "attribute_types/float4.h"

namespace imgui_markup::internal{

struct ObjectFloat4 : public Object
{
    ObjectFloat4(std::string id, Object* parent);

    ObjectFloat4& operator=(const ObjectFloat4& other);

    Float4 value;
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
