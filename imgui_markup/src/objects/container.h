#ifndef IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_

#include "objects/common/object_base.h"

namespace imgui_markup::internal{

struct Container : public ObjectBase
{
    Container(std::string id, ObjectBase* parent);

    Container& operator=(const Container& other);

    void Update();
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
