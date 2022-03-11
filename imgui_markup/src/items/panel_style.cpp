#include "impch.h"
#include "items/panel_style.h"

#include "items/panel.h"

namespace imgui_markup::internal
{

PanelStyle::PanelStyle(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kPanelStyle, id, parent)
{
    this->AddAttribute("background",            &this->background_);
    this->AddAttribute("title_background",      &this->title_background_);
    this->AddAttribute("title_background_active",
        &this->title_background_active_);
    this->AddAttribute("title_background_collapsed",
        &this->title_background_collapsed_);
    this->AddAttribute("title_align",           &this->title_align_);
    this->AddAttribute("scrollbar_background",  &this->scrollbar_background_);
    this->AddAttribute("scrollbar_grab",        &this->scrollbar_grab_);
    this->AddAttribute("scrollbar_grab_hovered",
        &this->scrollbar_grab_hovered_);
    this->AddAttribute("scrollbar_grab_active", &this->scrollbar_grab_active_);
    this->AddAttribute("padding",               &this->padding_);
    this->AddAttribute("rounding",              &this->rounding_);
    this->AddAttribute("border_size",           &this->border_size_);
    this->AddAttribute("border_color",          &this->border_color_);
}

void PanelStyle::PushStyle()
{
    if (this->background_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, this->background_);
        this->style_color_count_++;
    }

    if (this->title_background_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_TitleBg, this->title_background_);
        this->style_color_count_++;
    }

    if (this->title_background_active_.value_changed_)
    {
        ImGui::PushStyleColor(
            ImGuiCol_TitleBgActive, this->title_background_active_);
        this->style_color_count_++;
    }

    if (this->title_background_collapsed_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,
            this->title_background_collapsed_);
        this->style_color_count_++;
    }

    if (this->title_align_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, this->title_align_);
        this->style_var_count_++;
    }

    if (this->scrollbar_background_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg,
            this->scrollbar_background_);
        this->style_color_count_++;
    }

    if (this->scrollbar_grab_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, this->scrollbar_grab_);
        this->style_color_count_++;
    }

    if (this->scrollbar_grab_hovered_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered,
            this->scrollbar_grab_hovered_);
        this->style_color_count_++;
    }

    if (this->scrollbar_grab_active_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive,
            this->scrollbar_grab_active_);
        this->style_color_count_++;
    }

    if (this->padding_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, this->padding_);
        this->style_var_count_++;
    }

    if (this->rounding_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, this->rounding_);
        this->style_var_count_++;
    }

    if (this->border_size_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, this->border_size_);
        this->style_var_count_++;
    }

    if (this->border_color_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_Border, this->border_color_);
        this->style_color_count_++;
    }
}

void PanelStyle::PopStyle()
{
    ImGui::PopStyleColor(this->style_color_count_);
    ImGui::PopStyleVar(this->style_var_count_);
    this->style_color_count_ = 0;
    this->style_var_count_ = 0;
}

bool PanelStyle::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
    {
        error_message = "Item of type \"PanelStyle\" can only be created "
                        "insdie an item of type \"Button\"";
        return false;
    }

    if (this->parent_->GetType() != ItemType::kPanel)
    {
        error_message = "Item of type \"PanelStyle\" can only be created "
                        "insdie an item of type \"Button\"";
        return false;
    }

    Panel* parent = dynamic_cast<Panel*>(this->parent_);
    parent->style_ = this;

    return true;
}

}  // namespace imgui_markup::internal
