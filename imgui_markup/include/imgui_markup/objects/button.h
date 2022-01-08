#ifndef IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
#define IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_

#include "imgui_markup/objects/common/object.h"

#include "imgui_markup/attribute_types/float2.h"
#include "imgui_markup/attribute_types/float4.h"
#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
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

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
