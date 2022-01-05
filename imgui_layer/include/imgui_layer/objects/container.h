#ifndef IMGUI_LAYER_SRC_OBJECTS_CONTAINER_H_
#define IMGUI_LAYER_SRC_OBJECTS_CONTAINER_H_

#include "imgui_layer/objects/common/object.h"

namespace gui
{

struct Container : public Object
{
    Container(std::string id, Object* parent);

    Container& operator=(const Container& other);

    void Update();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
