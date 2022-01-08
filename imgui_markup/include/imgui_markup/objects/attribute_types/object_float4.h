#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/float4.h"

namespace imgui_markup
{

struct ObjectFloat4 : public Object
{
    ObjectFloat4(std::string id, Object* parent);

    ObjectFloat4& operator=(const ObjectFloat4& other);

    Float4 value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT4_H_
