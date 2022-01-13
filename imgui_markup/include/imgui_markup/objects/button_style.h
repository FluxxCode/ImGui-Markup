#ifndef IMGUI_MARKUP_SRC_OBJECTS_BUTTON_STYLE_H_
#define IMGUI_MARKUP_SRC_OBJECTS_BUTTON_STYLE_H_

#include "imgui_markup/objects/common/object.h"
#include "imgui_markup/objects/button.h"

#include "imgui_markup/attribute_types/bool.h"
#include "imgui_markup/attribute_types/float.h"
#include "imgui_markup/attribute_types/float2.h"
#include "imgui_markup/attribute_types/float4.h"

namespace imgui_markup
{

class ButtonStyle : public Object
{
public:
    ButtonStyle(std::string id, Object* parent);

    ButtonStyle& operator=(const ButtonStyle& other) = delete;

    Float4 color_;            // ImGuiCol_Button
    Float4 color_active_;     // ImGuiCol_ButtonHovered
    Float4 color_hovered_;    // ImGuiCol_ButtonActive
    Float rounding_;          // ImGuiStyle::FrameRounding
    Float border_size_;       // ImGuiStyle::FrameBorderSize
    Float4 border_color_;     // ImGuiStyle::FrameBorderSize
    Float4 border_shadow_;    // ImGuiCol_BorderShadow

    void PushStyle();
    void PopStyle();

private:
    size_t style_color_count_ = 0;
    size_t style_var_count_ = 0;

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_OBJECTS_BUTTON_STYLE_H_
