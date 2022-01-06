#ifndef IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
#define IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_

#include "imgui_layer/objects/common/object.h"

#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/attribute_types/float4.h"
#include "imgui_layer/attribute_types/string.h"

namespace gui
{

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
    bool OnProcessEnd(std::string& error_message);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
