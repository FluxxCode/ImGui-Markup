#ifndef IMGUI_MARKUP_SRC_OBJECTS_STYLE_H_
#define IMGUI_MARKUP_SRC_OBJECTS_STYLE_H_

#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float4.h"
#include "attribute_types/int.h"

namespace imgui_markup::internal
{

/**
 * Wrapper above the imgui style.
*/
class Style
{
protected:
    // See imgui.h for documentation

    Float  alpha_;
    Float  disabled_alpha_;
    Float2 window_padding_;
    Float  window_rounding_;
    Float  window_border_size_;
    Float2 window_min_size_;
    Float2 window_title_align_;
    Int    window_menu_button_position_;
    Float  child_rounding_;
    Float  child_border_size_;
    Float  popup_rounding_;
    Float  popup_border_size_;
    Float2 frame_padding_;
    Float  frame_rounding_;
    Float  frame_border_size_;
    Float2 item_spacing_;
    Float2 item_inner_spacing_;
    Float2 cell_padding_;
    Float2 touch_extra_padding_;
    Float  indent_spacing_;
    Float  columns_min_spacing_;
    Float  scrollbar_size_;
    Float  scrollbar_rounding_;
    Float  grab_min_size_;
    Float  grab_rounding_;
    Float  log_slider_deadzone_;
    Float  tab_rounding_;
    Float  tab_border_size_;
    Float  tab_min_width_for_close_button_;
    Int    color_button_position_;
    Float2 button_text_align_;
    Float2 selectable_text_align_;
    Float2 display_window_padding_;
    Float2 display_safe_area_padding_;
    Float  mouse_cursor_scale_;
    Bool   anti_aliased_lines_;
    Bool   anti_aliased_lines_use_tex_;
    Bool   anti_aliased_fill_;
    Float  curve_tessellation_tol_;
    Float  circle_tessellation_max_error_;

    // Functions
    void AddStyleAttirbutes(std::map<std::string, AttributeBase*>& attribute_list);

    void OverwriteName(std::map<std::string, AttributeBase*>& attribute_list,
                       const std::string old_name,
                       const std::string new_name);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OBJECTS_STYLE_H_
