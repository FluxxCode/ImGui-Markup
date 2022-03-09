#include "impch.h"
#include "objects/button.h"

#include "objects/button_style.h"
#include "utility/imgui_conversion.h"

namespace imgui_markup::internal{

Button::Button(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kButton, id, parent)
{
    this->AddAttribute("size", &this->size_);
    this->AddAttribute("text", &this->text_);
}

void Button::IMPL_Update(Float2 position, Float2 size)
{
    if (this->style_)
        this->style_->PushStyle();

    ImGui::SetCursorPos(position);

    ImGui::Button(this->text_, this->size_);

    this->is_hovered_ = ImGui::IsItemHovered();

    if (size == Float2(0, 0))
        this->size_ = ImGui::GetItemRectSize();

    if (this->style_)
        this->style_->PopStyle();
}

bool Button::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ObjectType::kPanel)
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
        this->text_ = "##" + this->draw_id_;

    return true;
}

Bool Button::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool Button::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal