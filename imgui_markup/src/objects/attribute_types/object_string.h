#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_

#include "objects/common/object.h"
#include "attribute_types/string.h"

namespace imgui_markup
{

struct ObjectString : public Object
{
    ObjectString(std::string id, Object* parent);

    ObjectString& operator=(const ObjectString& other);

    String value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_STRING_H_
