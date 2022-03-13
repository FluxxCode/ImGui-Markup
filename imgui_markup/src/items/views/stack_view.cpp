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
    Float2 actual_size = size;

    if (this->init_attributes_)
        this->InitAttributes();

    this->BeginChild(position, size);

    if (this->finished_first_update_ &&
        this->child_size_.x <= 0 && this->child_size_.y <= 0)
    {
        this->EndChild(size, actual_size);
        return;
    }

    for (const auto& child : this->child_items_)
    {
        child->Update(this->child_position_, this->child_size_);

        if (this->orientation_ == enums::Orientation::kVertical)
        {
            actual_size.y += child->GetSize().y + this->item_spacing_;

            if (child->GetSize().x.value + this->padding_.y * 2 > actual_size.x)
                actual_size.x = child->GetSize().x.value + this->padding_.y * 2;

            this->child_position_.y += child->GetSize().y + item_spacing_;
        }
        else if (this->orientation_ == enums::Orientation::kHorizontal)
        {
            actual_size.x += child->GetSize().x + this->item_spacing_;

            if (child->GetSize().y.value + this->padding_.y * 2 > actual_size.y)
                actual_size.y = child->GetSize().y.value + this->padding_.y * 2;

            this->child_position_.x += child->GetSize().x + item_spacing_;
        }
    }

    if (this->orientation_ == enums::Orientation::kVertical)
        actual_size.y += this->padding_.y * 2 - this->item_spacing_;
    else if (this->orientation_ == enums::Orientation::kHorizontal)
        actual_size.x += this->padding_.x * 2 - this->item_spacing_;

    this->EndChild(size, actual_size);

    this->finished_first_update_ = true;
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
}

void StackView::BeginChild(Float2 position, Float2 size)
{
    this->position_ = position;

    if (!this->finished_first_update_)
        this->size_ = size;

    this->child_position_ = Float2(position.x + this->padding_.x,
                                   position.y + this->padding_.y);

    this->child_size_ = Float2(0.0f, 0.0f);
    if (this->orientation_ == enums::Orientation::kVertical)
        this->child_size_.x = this->size_.x.value - this->padding_.x.value * 2;
    else if (this->orientation_ == enums::Orientation::kHorizontal)
        this->child_size_.y = this->size_.y.value - this->padding_.y.value * 2;

    if (this->child_size_.x < 0)
        this->child_size_.x = 0;
    if (this->child_size_.y < 0)
        this->child_size_.y = 0;

    if (!this->in_panel_)
        return;

    this->child_position_ = this->padding_;

    ImGui::SetCursorPos(position);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

    ImGui::BeginChild(this->draw_id_.c_str(), this->size_, false);

    ImGui::PopStyleVar(2);
}

void StackView::EndChild(Float2 size, Float2 actual_item_size)
{
    this->size_ = size;

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
