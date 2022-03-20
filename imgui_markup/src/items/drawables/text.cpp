#include "impch.h"
#include "items/drawables/text.h"

#include "utility/imgui_conversion.h"

namespace igm::internal{

Text::Text(std::string id, ItemBase* parent)
    : DrawableBase(ItemType::kText, id, parent)
{
    this->AddAttribute("text", &this->text_);
    this->AddAttribute("color", &this->color_);
}

void Text::IMPL_Update(Float2 position, Float2 size)
{
    this->BeginItemArea(position, size);

    if (this->color_.value_changed_)
        ImGui::TextColored(this->color_, "%s", this->text_.value.c_str());
    else
        ImGui::Text("%s", this->text_.value.c_str());

    this->is_hovered_ = ImGui::IsItemHovered();

    this->EndItemArea(size, ImGui::GetItemRectSize());
}

bool Text::OnProcessStart(std::string& error_message)
{
    ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the texts parent items must be an item "
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

}  // namespace igm::internal
