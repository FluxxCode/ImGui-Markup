#include "impch.h"
#include "items/drawables/checkbox.h"

#include "utility/imgui_conversion.h"

namespace igm::internal
{

Checkbox::Checkbox(std::string id, ItemBase* parent)
    : DrawableBase(ItemType::kCheckbox, id, parent)
{
    this->AddAttribute("text",    &this->text_);
    this->AddAttribute("toggled", &this->is_checked_);
}

Checkbox& Checkbox::operator=(const Checkbox& other)
{
    for (auto& child : this->child_items_)
        child->SetParent(other.parent_);

    return *this;
}

void Checkbox::IMPL_Update(Float2 position, Float2 size)
{
    this->BeginItemArea(position, size);

    ImGui::Checkbox(this->text_, &this->is_checked_.value);

    this->is_hovered_ = ImGui::IsItemHovered();

    this->EndItemArea(size, ImGui::GetItemRectSize());
}

bool Checkbox::OnProcessStart(std::string& error_message)
{
    ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the checkbox parent items must be an item "
                    "of type \"Panel\".";
    return false;
}

bool Checkbox::OnProcessEnd(std::string& error_message)
{
    this->text_.value += "##" + this->draw_id_;

    return true;
}

Bool Checkbox::API_IsItemPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool Checkbox::API_IsItemHovered() const
{
    return this->is_hovered_;
}

Bool Checkbox::API_IsCheckboxChecked() const
{
    return this->is_checked_;
}

}  // namespace igm::internal
