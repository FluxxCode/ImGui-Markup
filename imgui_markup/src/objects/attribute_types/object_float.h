#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_

#include "objects/common/object_base.h"
#include "attribute_types/float.h"

namespace imgui_markup::internal{

struct ObjectFloat : public ObjectBase
{
    ObjectFloat(std::string id, ObjectBase* parent);
    ObjectFloat(const ObjectFloat&) = delete;

    Float value;
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_OBJECTS_ATTRIBUTE_TYPES_OBJECT_FLOAT_H_
