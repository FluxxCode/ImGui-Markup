#include "ilpch.h"
#include "imgui_layer/objects/button.h"

namespace gui
{

Button::Button(std::string id, Object* parent)
    : Object("Button", id, parent)
{
    this->AddAttribute("size",          &this->size_);
    this->AddAttribute("text",          &this->text_);
    this->AddAttribute("color",         &this->color_);
    this->AddAttribute("color_active",  &this->color_active_);
    this->AddAttribute("color_hovered", &this->color_hovered_);
}

Button& Button::operator=(const Button& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Button::Update()
{
    this->PushStyle();

    ImGui::SetCursorPos(this->draw_position_);

    if (ImGui::Button(this->text_, this->size_))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;

    this->size_ = ImGui::GetItemRectSize();

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

bool Button::OnProcessEnd(std::string& error_message)
{
    if (this->text_.value.empty())
        this->text_ = "##empty_button";

    return true;
}

}  // namespace gui
