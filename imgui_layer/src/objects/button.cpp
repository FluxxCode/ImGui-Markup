#include "ilpch.h"
#include "objects/button.h"

namespace gui
{

Button::Button(std::string id, Object* parent)
    : Object("Button", id, parent)
{
    this->AddAttribute("text",          &this->text_);
    this->AddAttribute("color",         &this->color_);
    this->AddAttribute("color_active",  &this->color_active_);
    this->AddAttribute("color_hovered", &this->color_hovered_);
}

void Button::Update()
{
    this->PushStyle();

    if (ImGui::Button(this->text_, this->size_))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;

    this->PopStyle();
}

bool Button::IsPressed()
{
    return this->is_pressed_;
}

void Button::PushStyle()
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

void Button::PopStyle()
{
    ImGui::PopStyleColor(this->style_count_);
    this->style_count_ = 0;
}

}  // namespace gui
