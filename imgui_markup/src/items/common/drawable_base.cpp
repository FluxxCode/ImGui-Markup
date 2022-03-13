#include "impch.h"
#include "items/common/drawable_base.h"

#include "imgui_fork.h"

namespace imgui_markup::internal
{

void DrawableBase::BeginItemArea(Float2 position, Float2 size)
{
    this->position_ = position;

    if (size.x != 0)
        this->size_.x = size.x;
    if (size.y != 0)
        this->size_.y = size.y;

    ImGui::SetCursorPos(position);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, this->window_padding_);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, this->window_rounding_);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, this->window_bg_color_);

    ImGui::BeginChild(
        std::string(this->draw_id_ + "area").c_str(), this->size_, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    this->is_visible_ = ImGui::IsWindowActiveAndVisible();
    if (!this->is_visible_)
    {
        // We won't create the item area if it's not visible.
        // If we did that it would lead to all childs having a size of 0
        // because they are no longer updated. This will result in broken
        // scroll areas and generally broken size calculations.

        ImGui::EndChild();
        ImGui::SetCursorPos(position);
    }

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(1);
}

void DrawableBase::EndItemArea(Float2 size, Float2 actual_item_size)
{
    if (size.x == 0)
        this->size_.x = actual_item_size.x;
    if (size.y == 0)
        this->size_.y = actual_item_size.y;

    if (this->is_visible_)
        ImGui::EndChild();
}

}  // namespace imgui_markup::internal
