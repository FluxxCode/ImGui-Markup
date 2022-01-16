#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_COMMON_WINDOW_FLAGS_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_COMMON_WINDOW_FLAGS_H_

#include "imgui_markup/attribute_types/bool.h"

#include <map>
#include <string>

namespace imgui_markup
{

/**
 * Wrapper above the ImGuiWindowFlags
 */
class WindowFlags
{
protected:
    Bool no_title_bar_                = false;
    Bool no_resize_                   = false;
    Bool no_move_                     = false;
    Bool no_scrollbar_                = false;
    Bool no_scroll_with_mouse_        = false;
    Bool no_collapse_                 = false;
    Bool always_auto_resize_          = false;
    Bool no_background_               = false;
    // Bool no_saved_settings_          = false;
    Bool no_mouse_inputs_             = false;
    // Bool menu_bar_                    = false;
    Bool horizontal_scrollbar_        = false;
    Bool no_focus_on_appearing_       = false;
    Bool no_bring_to_front_focus_     = false;
    Bool always_vertical_scrollbar_   = false;
    Bool always_horizontal_scrollbar_ = false;
    // Bool always_use_window_padding_   = false;
    Bool no_nav_inputs_               = false;
    Bool no_nav_focus_                = false;
    Bool unsaved_document_            = false;
    Bool no_nav_                      = false;
    Bool no_decoration_               = false;
    Bool no_inputs_                   = false;

    /**
     * Adds the window flags attributes to the given attribute list.
     */
    void InitWindowFlagAttributes(
        std::map<std::string, Attribute*>& attribute_list);

    /**
     * Generates the ImGuiWindowFlags based on the attributes from this object.
     *
     * @return ImGuiWindowFlags
     */
    int GenerateWindowFlags() const;

};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_OBJECTS_COMMON_WINDOW_FLAGS_H_
