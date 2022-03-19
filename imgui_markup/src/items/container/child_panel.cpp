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
    this->InitPositionAndSize(position, size);

    ImGui::SetCursorPos(position);

    ImGui::BeginChild(this->title_, this->size_, this->border_.value,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    this->is_hovered_ = ImGui::IsWindowHovered();

    Float2 actual_size = Float2(1.0f, 1.0f);

    for (auto& child : this->child_items_)
    {
        if (!child)
            continue;

        child->Update(this->CalculateChildPosition(),
                      this->CalculateChildSize(size));

        if (child->GetCategory() != ItemCategory::kStyle &&
            child->GetCategory() != ItemCategory::kOther)
        {
            actual_size = child->GetSize();
        }
    }

    ImGui::EndChild();

    actual_size.x += this->padding_.x * 2;
    actual_size.y += this->padding_.y * 2;

    if (size.x == 0)
        this->size_.x = actual_size.x;
    if (size.y == 0)
        this->size_.y = actual_size.y;
}

void ChildPanel::InitPositionAndSize(Float2 position, Float2 size)
{
    this->position_ = position;

    if (size.x != 0)
        this->size_.x = size.x;
    if (size.y != 0)
        this->size_.y = size.y;
}

Float2 ChildPanel::CalculateChildPosition() const
{
    return this->padding_;
}

Float2 ChildPanel::CalculateChildSize(Float2 size) const
{
    Float2 child_size = Float2(this->size_.x.value - this->padding_.x * 2,
                               this->size_.y.value - this->padding_.y * 2);

    if (child_size.x < 0)
        child_size.x = 0;
    if (child_size.y < 0)
        child_size.y = 0;

    return child_size;
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
