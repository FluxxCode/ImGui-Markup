#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_

#include "objects/common/object_base.h"
#include "attribute_types/float2.h"

namespace imgui_markup::internal
{

struct ObjectFloat2 : public ObjectBase
{
    ObjectFloat2(std::string id, ObjectBase* parent);
    ObjectFloat2(const ObjectFloat2&) = delete;

    Float2 value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
