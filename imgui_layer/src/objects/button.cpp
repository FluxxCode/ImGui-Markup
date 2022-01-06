#include "ilpch.h"
#include "imgui_layer/objects/button.h"

#include "imgui_layer/objects/button_style.h"

namespace gui
{

Button::Button(std::string id, Object* parent)
    : Object("Button", id, parent)
{
    this->AddAttribute("size", &this->size_);
    this->AddAttribute("text", &this->text_);
}

Button& Button::operator=(const Button& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Button::Update()
{
    if (this->style_)
        this->style_->PushStyle();

    ImGui::SetCursorPos(this->draw_position_);

    if (ImGui::Button(this->text_, this->size_))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;

    this->size_ = ImGui::GetItemRectSize();

    if (this->style_)
        this->style_->PopStyle();
}

bool Button::IsPressed()
{
    return this->is_pressed_;
}

bool Button::OnProcessEnd(std::string& error_message)
{
    if (this->text_.value.empty())
        this->text_ = "##empty_button";

    return true;
}

}  // namespace gui
