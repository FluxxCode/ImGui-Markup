#include "impch.h"
#include "objects/text.h"

#include "utility/imgui_conversion.h"

namespace imgui_markup::internal{

Text::Text(std::string id, ObjectBase* parent)
    : ObjectBase("Text", id, parent)
{
    this->AddAttribute("text", &this->text_);
    this->AddAttribute("color", &this->color_);
}

void Text::IMPL_Update()
{
    ImGui::SetCursorPos(this->draw_position_);

    if (this->color_.value_changed_)
        ImGui::TextColored(this->color_, "%s", this->text_.value.c_str());
    else
        ImGui::Text("%s", this->text_.value.c_str());

    this->is_hovered_ = ImGui::IsItemHovered();

    this->size_ = ImGui::GetItemRectSize();
}

bool Text::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == "Panel")
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the texts parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

bool Text::OnProcessEnd(std::string& error_message)
{
    if (this->text_.value.empty())
        this->text_ = "##" + this->draw_id_;

    return true;
}

Bool Text::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool Text::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal
