#ifndef IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_
#define IMGUI_MARKUP_SRC_OBJECTS_CONTAINER_H_

#include "objects/common/object_base.h"

namespace imgui_markup::internal
{

class Container : public ObjectBase
{
public:
    Container(std::string id, ObjectBase* parent);
    Container(const Container&) = delete;

private:
    // See object.h for documentation
    void IMPL_Update();
    bool OnProcessStart(std::string& error_message);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
