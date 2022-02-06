#ifndef IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_API_H_
#define IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_API_H_

#include "attribute_types/bool.h"

namespace imgui_markup::internal
{

struct ObjectAPI
{

virtual Bool API_IsPressed() const { return false; }

};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_COMMON_OBJECT_API_H_
