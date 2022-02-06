#include "impch.h"
#include "objects/common/window_flags.h"

namespace imgui_markup
{

void WindowFlags::InitWindowFlagAttributes(
    std::map<std::string, Attribute*>& attribute_list)
{
    attribute_list["no_title_bar"]            = &this->no_title_bar_;
    attribute_list["no_resize"]               = &this->no_resize_;
    attribute_list["no_move"]                 = &this->no_move_;
    attribute_list["no_scrollbar"]            = &this->no_scrollbar_;
    attribute_list["no_scroll_with_mouse"]    = &this->no_scroll_with_mouse_;
    attribute_list["no_collapse"]             = &this->no_collapse_;
    attribute_list["always_auto_resize"]      = &this->always_auto_resize_;
    attribute_list["no_background"]           = &this->no_background_;
    attribute_list["no_mouse_inputs"]         = &this->no_mouse_inputs_;
    attribute_list["horizontal_scrollbar"]    = &this->horizontal_scrollbar_;
    attribute_list["no_focus_on_appearing"]   = &this->no_focus_on_appearing_;
    attribute_list["no_bring_to_front_focus"] = &this->no_bring_to_front_focus_;
    attribute_list["always_vertical_scrollbar"] =
        &this->always_vertical_scrollbar_;
    attribute_list["always_horizontal_scrollbar"] =
        &this->always_horizontal_scrollbar_;
    attribute_list["no_nav_inputs"]    = &this->no_nav_inputs_;
    attribute_list["no_nav_focus"]     = &this->no_nav_focus_;
    attribute_list["unsaved_document"] = &this->unsaved_document_;
    attribute_list["no_nav"]           = &this->no_nav_;
    attribute_list["no_decoration"]    = &this->no_decoration_;
    attribute_list["no_inputs"]        = &this->no_inputs_;
}

int WindowFlags::GenerateWindowFlags() const
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;

    if (this->no_title_bar_)
        flags |= ImGuiWindowFlags_NoTitleBar;
    if (this->no_resize_)
        flags |= ImGuiWindowFlags_NoResize;
    if (this->no_move_)
        flags |= ImGuiWindowFlags_NoMove;
    if (this->no_scrollbar_)
        flags |= ImGuiWindowFlags_NoScrollbar;
    if (this->no_scroll_with_mouse_)
        flags |= ImGuiWindowFlags_NoScrollWithMouse;
    if (this->no_collapse_)
        flags |= ImGuiWindowFlags_NoCollapse;
    if (this->always_auto_resize_)
        flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (this->no_background_)
        flags |= ImGuiWindowFlags_NoBackground;
    if (this->no_mouse_inputs_)
        flags |= ImGuiWindowFlags_NoMouseInputs;
    if (this->horizontal_scrollbar_)
        flags |= ImGuiWindowFlags_HorizontalScrollbar;
    if (this->no_focus_on_appearing_)
        flags |= ImGuiWindowFlags_NoFocusOnAppearing;
    if (this->no_bring_to_front_focus_)
        flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (this->always_vertical_scrollbar_)
        flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
    if (this->always_horizontal_scrollbar_)
        flags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
    if (this->no_nav_inputs_)
        flags |= ImGuiWindowFlags_NoNavInputs;
    if (this->no_nav_focus_)
        flags |= ImGuiWindowFlags_NoNavFocus;
    if (this->unsaved_document_)
        flags |= ImGuiWindowFlags_UnsavedDocument;
    if (this->no_nav_)
        flags |= ImGuiWindowFlags_NoNav;
    if (this->no_decoration_)
        flags |= ImGuiWindowFlags_NoDecoration;
    if (this->no_inputs_)
        flags |= ImGuiWindowFlags_NoInputs;

    return flags;
}

}  // namespace imgui_markup
