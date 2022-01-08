#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/attribute_types/int.h"

namespace imgui_markup
{

struct ObjectInt : public Object
{
    ObjectInt(std::string id, Object* parent);

    ObjectInt& operator=(const ObjectInt& other);

    Int value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
