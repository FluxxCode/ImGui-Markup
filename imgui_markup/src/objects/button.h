#ifndef IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
#define IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_

#include "objects/common/object.h"

#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal{

class ButtonStyle;

class Button : public Object
{
public:
    Button(std::string id, Object* parent);

    Button& operator=(const Button& other);

    void Update();
    bool IsPressed();

    String text_;

private:
    friend class ButtonStyle;

    bool is_pressed_ = false;
    ButtonStyle* style_ = nullptr;

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_H_
