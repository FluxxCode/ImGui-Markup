#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_

#include "objects/common/object.h"
#include "attribute_types/float2.h"

namespace imgui_markup
{

struct ObjectFloat2 : public Object
{
    ObjectFloat2(std::string id, Object* parent);

    ObjectFloat2& operator=(const ObjectFloat2& other);

    Float2 value;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT2_H_
