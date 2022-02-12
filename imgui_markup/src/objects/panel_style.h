#ifndef IMGUI_MARKUP_SRC_OBJECTS_PANEL_STYLE_H_
#define IMGUI_MARKUP_SRC_OBJECTS_PANEL_STYLE_H_

#include "objects/common/object_base.h"

#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float4.h"

namespace imgui_markup::internal{

class PanelStyle : public ObjectBase
{
public:
    PanelStyle(std::string id, ObjectBase* parent);

    PanelStyle& operator=(const PanelStyle& other) = delete;

    Float4 background_;                  // ImGuiCol_WindowBg
    Float4 title_background_;            // ImGuiCol_TitleBg
    Float4 title_background_active_;     // ImGuiCol_TitleBgActive
    Float4 title_background_collapsed_;  // ImGuiCol_TitleBgCollapsed
    Float2 title_align_;                 // ImGuiStyle::TitleAlign
    Float4 scrollbar_background_;        // ImGuiCol_ScrollbarBg
    Float4 scrollbar_grab_;              // ImGuiCol_ScrollbarGrab
    Float4 scrollbar_grab_hovered_;      // ImGuiCol_ScrollbarGrabHovered
    Float4 scrollbar_grab_active_;       // ImGuiCol_ScrollbarGrabActive
    Float2 padding_;                     // ImGuiStyle::WindowPadding
    Float rounding_;                     // ImGuiStyle::FrameRounding
    Float border_size_;                  // ImGuiStyle::FrameBorderSize
    Float4 border_color_;                // ImGuiStyle::FrameBorderSize

    void PushStyle();
    void PopStyle();

private:
    size_t style_color_count_ = 0;
    size_t style_var_count_ = 0;

    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_PANEL_STYLE_H_
