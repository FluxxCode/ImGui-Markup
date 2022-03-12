#include "impch.h"
#include "items/container/child_panel.h"

#include "utility/imgui_conversion.h"

namespace imgui_markup::internal
{

ChildPanel::ChildPanel(std::string id, ItemBase* parent)
    : ContainerBase(ItemType::kChildPanel, id, parent)
{
    this->AddAttribute("title",   &this->title_);
    this->AddAttribute("border",  &this->border_);
    this->AddAttribute("padding", &this->padding_);
}

void ChildPanel::IMPL_Update(Float2 position, Float2 size)
{
    this->position_ = position;
    this->size_ = size;

    ImGui::SetCursorPos(position);

    ImGui::BeginChild(this->title_, size, this->border_.value,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    this->is_hovered_ = ImGui::IsWindowHovered();

    const Float2 child_size = Float2(
        this->size_.x.value - this->padding_.x.value * 2,
        this->size_.y.value - this->padding_.y.value * 2);

    const Float2 child_position = Float2(this->padding_.x, this->padding_.y);

    for (auto& child : this->child_items_)
    {
        if (!child)
            continue;

        child->Update(child_position, child_size);
    }

    ImGui::EndChild();
}

bool ChildPanel::OnProcessStart(std::string& error_message)
{
    ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the child panels parent items must be an item "
                    "of type \"Panel\".";
    return false;
}

bool ChildPanel::OnProcessEnd(std::string& error_message)
{
    size_t child_count = 0;
    for (const auto& child : this->child_items_)
    {
        const ItemCategory category = child->GetCategory();

        if (category != ItemCategory::kStyle &&
            category != ItemCategory::kOther)
        {
            child_count++;
        }
    }

    if (child_count > 1)
    {
        error_message = "Object of type \"ChildPanel\" can only contain one "
                        "drawable object\".";

        return false;
    }

    this->title_.value += "##" + this->draw_id_;

    return true;
}

Bool ChildPanel::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool ChildPanel::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal
