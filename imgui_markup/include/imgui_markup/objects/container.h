#ifndef IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_

#include "imgui_markup/objects/common/object.h"

namespace imgui_markup
{

struct Container : public Object
{
    Container(std::string id, Object* parent);

    Container& operator=(const Container& other);

    void Update();
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
