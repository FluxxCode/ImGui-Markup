#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/bool.h"

namespace imgui_markup
{

struct ObjectBool : public Object
{
    ObjectBool(std::string id, Object* parent);

    ObjectBool& operator=(const ObjectBool& other);

    Bool value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_BOOL_H_
