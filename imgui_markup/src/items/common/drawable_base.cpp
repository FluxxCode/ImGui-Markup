#include "impch.h"
#include "items/common/drawable_base.h"

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

    ImGui::BeginChild(std::string(this->draw_id_ + "area").c_str(), size, false,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(1);
}

void DrawableBase::EndItemArea(Float2 size, Float2 actual_item_size)
{
    if (size.x == 0)
        this->size_.x = actual_item_size.x;
    if (size.y == 0)
        this->size_.y = actual_item_size.y;

    ImGui::EndChild();
}

}  // namespace imgui_markup::internal
