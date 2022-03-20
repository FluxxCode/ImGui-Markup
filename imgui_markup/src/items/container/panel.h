#ifndef IMGUI_MARKUP_SRC_ITEMS_CONTAINER_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEMS_CONTAINER_PANEL_H_

#include "items/common/container_base.h"

#include "attribute_types/bool.h"
#include "attribute_types/string.h"
#include "attribute_types/float2.h"

namespace igm::internal
{

class PanelStyle;

class Panel : public ContainerBase
{
public:
    // Constructor/Destructor
    Panel(std::string id, ItemBase* parent);
    Panel(const Panel&) = delete;

    Float2 position_overwrite_;
    Float2 size_overwrite_;
    String title_;
    Float2 padding_ = Float2(0.0f, 0.0f);

    // Flags:
    Bool no_title_bar_             = false;
    Bool no_resize_                = false;
    Bool no_move_                  = false;
    Bool no_collapse_              = false;
    Bool always_auto_resize_       = false;
    Bool no_background_            = false;
    Bool no_mouse_inputs_          = false;
    Bool no_focus_on_appearing_    = false;
    Bool no_bring_to_front_focus_  = false;
    Bool no_nav_inputs_            = false;
    Bool no_nav_focus_             = false;
    Bool unsaved_document_         = false;
    Bool no_nav_                   = false;
    Bool no_decoration_            = false;
    Bool no_inputs_                = false;

    // Flags that can't be set through the markup language
    Bool no_scroll_with_mouse_ = true;
    Bool no_scrollbar_         = true;
    Bool horizontal_scrollbar_ = false;
    Bool always_vertical_scrollbar_   = false;
    Bool always_horizontal_scrollbar_ = false;

    // Flags we don't need but ImGui supports
    // Bool always_use_window_padding_ = false;
    // Bool menu_bar_ = false;
    // Bool no_saved_settings_ = false;

private:
    friend class PanelStyle;
    PanelStyle* style_ = nullptr;

    bool is_hovered_ = false;

    Float2 child_position_;
    Float2 child_size_;

    float title_bar_height_ = 17;
    bool in_view_ = false;  // If the panel is placed inside a view

    bool finished_first_update_ = false;
    bool init_position_and_size_ = true;

    bool BeginPanel();
    void EndPanel(Float2 size, Float2 actual_size);

    void InitPositionAndSize(Float2 position, Float2 size);

    void UpdateChildPositionAndSize();
    float CalcTitleBarHeight() const;
    int GenerateWindowFlags() const;

    // See item.h for documentation
    void IMPL_Update(Float2 position, Float2 size);
    bool OnProcessStart(std::string& error_message);
    bool OnProcessEnd(std::string& error_message);

    // See item_api.h for documentation
    Bool API_IsPressed(MouseButton button) const;
    Bool API_IsHovered() const;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_CONTAINER_PANEL_H_
