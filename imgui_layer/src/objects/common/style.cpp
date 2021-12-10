#include "ilpch.h"
#include "imgui_layer/objects/common/style.h"

namespace gui
{

void Style::AddStyleAttirbutes(
    std::map<std::string, AttributeType*>& attribute_list)
{
    attribute_list["alpha"]
        = &this->alpha_;
    attribute_list["disabled_alpha"]
        = &this->disabled_alpha_;
    attribute_list["window_padding"]
        = &this->window_padding_;
    attribute_list["window_rounding"]
        = &this->window_rounding_;
    attribute_list["window_border_size"]
        = &this->window_border_size_;
    attribute_list["window_min_size"]
        = &this->window_min_size_;
    attribute_list["window_title_align"]
        = &this->window_title_align_;
    attribute_list["window_menu_button_position"]
        = &this->window_menu_button_position_;
    attribute_list["child_rounding"]
        = &this->child_rounding_;
    attribute_list["child_border_size"]
        = &this->child_border_size_;
    attribute_list["popup_rounding"]
        = &this->popup_rounding_;
    attribute_list["popup_border_size"]
        = &this->popup_border_size_;
    attribute_list["frame_padding"]
        = &this->frame_padding_;
    attribute_list["frame_rounding"]
        = &this->frame_rounding_;
    attribute_list["frame_border_size"]
        = &this->frame_border_size_;
    attribute_list["item_spacing"]
        = &this->item_spacing_;
    attribute_list["item_inner_spacing"]
        = &this->item_inner_spacing_;
    attribute_list["cell_padding"]
        = &this->cell_padding_;
    attribute_list["touch_extra_padding"]
        = &this->touch_extra_padding_;
    attribute_list["indent_spacing"]
        = &this->indent_spacing_;
    attribute_list["indent_spacing"]
        = &this->indent_spacing_;
    attribute_list["scrollbar_size"]
        = &this->scrollbar_size_;
    attribute_list["scrollbar_rounding"]
        = &this->scrollbar_rounding_;
    attribute_list["grab_min_size"]
        = &this->grab_min_size_;
    attribute_list["grab_rounding"]
        = &this->grab_rounding_;
    attribute_list["log_slider_deadzone"]
        = &this->log_slider_deadzone_;
    attribute_list["tab_rounding"]
        = &this->tab_rounding_;
    attribute_list["tab_border_size"]
        = &this->tab_border_size_;
    attribute_list["tab_min_width_for_close_button"]
        = &this->tab_min_width_for_close_button_;
    attribute_list["color_button_position"]
        = &this->color_button_position_;
    attribute_list["button_text_align"]
        = &this->button_text_align_;
    attribute_list["selectable_text_align"]
        = &this->selectable_text_align_;
    attribute_list["display_window_padding"]
        = &this->display_window_padding_;
    attribute_list["display_safe_area_padding"]
        = &this->display_safe_area_padding_;
    attribute_list["mouse_cursor_scale"]
        = &this->mouse_cursor_scale_;
    attribute_list["anti_aliased_lines"]
        = &this->anti_aliased_lines_;
    attribute_list["anti_aliased_lines_use_tex"]
        = &this->anti_aliased_lines_use_tex_;
    attribute_list["anti_aliased_fill"]
        = &this->anti_aliased_fill_;
    attribute_list["curve_tessellation_tol"]
        = &this->curve_tessellation_tol_;
    attribute_list["circle_tessellation_max_error"]
        = &this->circle_tessellation_max_error_;
}

void Style::OverwriteName(
    std::map<std::string, AttributeType*>& attribute_list,
    const std::string old_name,
    const std::string new_name)
{
    if (attribute_list.find(old_name) == attribute_list.end())
        return;

    AttributeType* value = attribute_list[old_name];
    attribute_list.erase(old_name);
    attribute_list[new_name] = value;
}

}  // namespace gui
