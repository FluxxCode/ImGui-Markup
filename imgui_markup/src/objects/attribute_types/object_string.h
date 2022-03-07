#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_

#include "objects/common/object_base.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal
{

struct ObjectString : public ObjectBase
{
    ObjectString(std::string id, ObjectBase* parent);
    ObjectString(const ObjectString&) = delete;

    String value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
