#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_

#include "objects/common/object_base.h"
#include "attribute_types/int.h"

namespace imgui_markup::internal{

struct ObjectInt : public ObjectBase
{
    ObjectInt(std::string id, ObjectBase* parent);

    ObjectInt& operator=(const ObjectInt& other);

    Int value;
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_INT_H_
