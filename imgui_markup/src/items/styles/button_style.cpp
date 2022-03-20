#include "impch.h"
#include "items/styles/button_style.h"

namespace igm::internal
{

ButtonStyle::ButtonStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kButtonStyle, id, parent)
{
    this->AddAttribute("color",           &this->color_);
    this->AddAttribute("color_hovered",   &this->color_hovered_);
    this->AddAttribute("color_active",    &this->color_active_);
    this->AddAttribute("rounding",        &this->rounding_);
    this->AddAttribute("border_size",     &this->border_size_);
    this->AddAttribute("border_color",    &this->border_color_);
    this->AddAttribute("border_shadow",   &this->border_shadow_);
}

void ButtonStyle::PushStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Colors
    if (this->color_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, this->color_);
        this->style_color_count_++;
    }

    if (this->color_active_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, this->color_active_);
        this->style_color_count_++;
    }

    if (this->color_hovered_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, this->color_hovered_);
        this->style_color_count_++;
    }

    if (this->rounding_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, this->rounding_);
        this->style_var_count_++;
    }

    if (this->border_size_.value_changed_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, this->border_size_);
        this->style_var_count_++;
    }

    if (this->border_color_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_Border, this->border_color_);
        this->style_color_count_++;
    }

    if (this->border_shadow_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, this->border_shadow_);
        this->style_color_count_++;
    }
}

void ButtonStyle::PopStyle()
{
    ImGui::PopStyleColor(this->style_color_count_);
    ImGui::PopStyleVar(this->style_var_count_);
    this->style_color_count_ = 0;
    this->style_var_count_ = 0;
}

bool ButtonStyle::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
    {
        error_message = "Item of type \"ButtonStyle\" can only be created "
                        "insdie an item of type \"Button\"";
        return false;
    }

    if (this->parent_->GetType() != ItemType::kButton)
    {
        error_message = "Item of type \"ButtonStyle\" can only be created "
                        "insdie an item of type \"Button\"";
        return false;
    }

    Button* parent = dynamic_cast<Button*>(this->parent_);
    parent->style_ = this;

    return true;
}

}  // namespace igm::internal
