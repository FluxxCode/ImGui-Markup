#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_

#include "objects/common/object_base.h"
#include "attribute_types/float3.h"

namespace imgui_markup::internal
{

struct ObjectFloat3 : public ObjectBase
{
    ObjectFloat3(std::string id, ObjectBase* parent);
    ObjectFloat3(const ObjectFloat3&) = delete;

    Float3 value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT3_H_
