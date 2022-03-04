#include "impch.h"
#include "objects/checkbox.h"

#include "utility/imgui_conversion.h"

namespace imgui_markup::internal
{

Checkbox::Checkbox(std::string id, ObjectBase* parent)
    : ObjectBase("Checkbox", id, parent)
{
    this->AddAttribute("text",    &this->text_);
    this->AddAttribute("toggled", &this->is_toggled_);
}

Checkbox& Checkbox::operator=(const Checkbox& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Checkbox::IMPL_Update()
{
    ImGui::SetCursorPos(this->draw_position_);

    ImGui::Checkbox(this->text_, &this->is_toggled_.value);

    this->is_hovered_ = ImGui::IsItemHovered();
    this->size_ = ImGui::GetItemRectSize();
}

bool Checkbox::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == "Panel")
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the checkbox parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

bool Checkbox::OnProcessEnd(std::string& error_message)
{
    this->text_.value += "##" + this->draw_id_;

    return true;
}

Bool Checkbox::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool Checkbox::API_IsHovered() const
{
    return this->is_hovered_;
}

Bool Checkbox::API_IsToggled() const
{
    return this->is_toggled_;
}

}  // namespace imgui_markup::internal
