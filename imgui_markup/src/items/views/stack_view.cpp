#include "impch.h"
#include "items/views/stack_view.h"

#include "utility/imgui_conversion.h"
#include "items/styles/panel_style.h"

namespace imgui_markup::internal
{

StackView::StackView(std::string id, ItemBase* parent)
    : ViewBase(ItemType::kStackView, id, parent)
{
    this->AddAttribute("orientation",  &this->orientation_);
    this->AddAttribute("padding",      &this->padding_);
    this->AddAttribute("item_spacing", &this->item_spacing_);
}

void StackView::IMPL_Update(Float2 position, Float2 size)
{
    Float2 actual_size = Float2(0.0f, 0.0f);

    if (this->orientation_ == enums::Orientation::kVertical)
        actual_size.x = size.x;
    else
        actual_size.y = size.x;

    if (this->init_attributes_)
        this->InitAttributes();

    this->BeginChild(position, size);

    if (this->child_size_.x <= 0 && this->child_size_.y <= 0)
    {
        this->EndChild(size, actual_size);
        return;
    }

    for (const auto& child : this->child_items_)
    {
        child->Update(this->child_position_, this->child_size_);

        float offset = this->item_spacing_;
        if (this->orientation_ == enums::Orientation::kVertical)
        {
            offset += child->GetSize().y;
            this->child_position_.y += offset;
            actual_size.y += offset;
        }
        else
        {
            offset += child->GetSize().x;
            this->child_position_.x += offset;
            actual_size.x += offset;
        }
    }

    this->EndChild(size, actual_size);
}

void StackView::InitAttributes()
{
    this->init_attributes_ = false;

    if (this->item_spacing_.value_changed_)
        return;

    if (this->orientation_ == enums::Orientation::kVertical)
        this->item_spacing_ = ImGui::GetStyle().ItemSpacing.y;
    else
        this->item_spacing_ = ImGui::GetStyle().ItemSpacing.x;

    this->init_attributes_ = false;
}

void StackView::BeginChild(Float2 position, Float2 size)
{
    this->position_ = position;

    this->child_position_ = Float2(position.x + this->padding_.x,
                                   position.y + this->padding_.y);

    this->child_size_ = Float2(0.0f, 0.0f);

    if (this->orientation_ == enums::Orientation::kVertical)
        this->child_size_.x = this->size_.x.value - this->padding_.x.value * 2;
    else
        this->child_size_.y = this->size_.y.value - this->padding_.y.value * 2;

    if (size.x != 0)
        this->size_.x = size.x;
    if (size.y !=  0)
        this->size_.y = size.y;

    if (!this->in_panel_)
        return;

    this->child_position_ = this->padding_;

    ImGui::SetCursorPos(position);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::BeginChild(this->draw_id_.c_str(), this->size_, this->border_);

    ImGui::PopStyleVar(1);
}

void StackView::EndChild(Float2 size, Float2 actual_item_size)
{
    if (size.x == 0)
        this->size_.x = actual_item_size.x;
    if (size.y == 0)
        this->size_.y = actual_item_size.y;

    if (!this->in_panel_)
        return;

    ImGui::EndChild();
}

bool StackView::OnProcessStart(std::string& error_message)
{
    ItemBase* parent = this->parent_;

    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
        {
            this->in_panel_ = true;
            break;
        }

        parent = parent->GetParent();
    }

    return true;
}

Bool StackView::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool StackView::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal
