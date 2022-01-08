#include "impch.h"
#include "imgui_markup/objects/button_style.h"

namespace imgui_markup
{

ButtonStyle::ButtonStyle(std::string id, Object* parent)
    : Object("ButtonStyle", id, parent)
{
    this->AddAttribute("color",         &this->color_);
    this->AddAttribute("color_hovered", &this->color_hovered_);
    this->AddAttribute("color_active",  &this->color_active_);
}

void ButtonStyle::PushStyle()
{
    if (this->color_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, this->color_);
        this->style_count_++;
    }

    if (this->color_active_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, this->color_active_);
        this->style_count_++;
    }

    if (this->color_hovered_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, this->color_hovered_);
        this->style_count_++;
    }
}

void ButtonStyle::PopStyle()
{
    ImGui::PopStyleColor(this->style_count_);
    this->style_count_ = 0;
}

bool ButtonStyle::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
    {
        error_message = "Object of type \"ButtonStyle\" can only be created "
                        "insdie an object of type \"Button\"";
        return false;
    }

    if (this->parent_->GetType() != "Button")
    {
        error_message = "Object of type \"ButtonStyle\" can only be created "
                        "insdie an object of type \"Button\"";
        return false;
    }

    Button* parent = dynamic_cast<Button*>(this->parent_);
    parent->style_ = this;

    return true;
}

}  // namespace imgui_markup
