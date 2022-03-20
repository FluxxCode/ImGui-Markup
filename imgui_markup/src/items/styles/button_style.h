#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLES_BUTTON_STYLE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLES_BUTTON_STYLE_H_

#include "items/common/style_base.h"
#include "items/drawables/button.h"

#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float4.h"

namespace igm::internal
{

class ButtonStyle : public StyleBase
{
public:
    ButtonStyle(std::string id, ItemBase* parent);
    ButtonStyle(const ButtonStyle&) = delete;

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

    // See item.h for documentation
    bool OnProcessStart(std::string& error_message);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLES_BUTTON_STYLE_H_
