#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_

#include "objects/common/object.h"
#include "attribute_types/bool.h"

namespace imgui_markup::internal
{

struct ObjectBool : public Object
{
    ObjectBool(std::string id, Object* parent);

    ObjectBool& operator=(const ObjectBool& other);

    Bool value;
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
