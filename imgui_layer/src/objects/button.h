#ifndef IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
#define IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_

#include "objects/object.h"

#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/string.h"

namespace gui
{

class Button : public Object
{
public:
    // Constructor/Destructor
    Button(std::string id, Object* parent);

    // Functions
    void Update();

    bool IsPressed();

    String text_;
    Float4 color_;
    Float4 color_active_;
    Float4 color_hovered_;

private:
    // Variables
    bool is_pressed_ = false;

    unsigned char style_count_ = 0;

    // Functions
    void PushStyle();
    void PopStyle();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_H_
