#ifndef IMGUI_LAYER_SRC_OBJECTS_BUTTON_STYLE_H_
#define IMGUI_LAYER_SRC_OBJECTS_BUTTON_STYLE_H_

#include "imgui_layer/objects/common/object.h"
#include "imgui_layer/objects/button.h"

#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/attribute_types/float4.h"

namespace gui
{

class ButtonStyle : public Object
{
public:
    ButtonStyle(std::string id, Object* parent);

    ButtonStyle& operator=(const ButtonStyle& other) = delete;

    Float4 color_;
    Float4 color_active_;
    Float4 color_hovered_;

    void PushStyle();
    void PopStyle();

private:
    size_t style_count_ = 0;

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_OBJECTS_BUTTON_STYLE_H_
