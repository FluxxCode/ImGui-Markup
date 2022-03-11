#include "impch.h"
#include "items/button.h"

#include "items/button_style.h"
#include "utility/imgui_conversion.h"

namespace imgui_markup::internal{

Button::Button(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kButton, id, parent)
{
    this->AddAttribute("size", &this->size_);
    this->AddAttribute("text", &this->text_);
}

void Button::IMPL_Update(Float2 position, Float2 size)
{
    this->size_ = size;
    this->position_ = position;

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
    ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the buttons parent items must be an item "
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