#include "impch.h"
#include "objects/button.h"

#include "objects/button_style.h"

namespace imgui_markup::internal{

Button::Button(std::string id, ObjectBase* parent)
    : ObjectBase("Button", id, parent)
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

bool Button::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == "Panel")
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the buttons parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

bool Button::OnProcessEnd(std::string& error_message)
{
    if (this->text_.value.empty())
        this->text_ = "##empty_button";

    return true;
}

Bool Button::API_IsPressed() const
{
    return this->is_pressed_;
}

}  // namespace imgui_markup::internal