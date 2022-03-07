#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_

#include "objects/common/object_base.h"
#include "attribute_types/float4.h"

namespace imgui_markup::internal
{

struct ObjectFloat4 : public ObjectBase
{
    ObjectFloat4(std::string id, ObjectBase* parent);
    ObjectFloat4(const ObjectFloat4&) = delete;

    Float4 value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
