#include "impch.h"
#include "items/container/panel.h"

#include "utility/imgui_conversion.h"
#include "items/styles/panel_style.h"

namespace imgui_markup::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : ContainerBase(ItemType::kPanel, id, parent)
{
    this->InitWindowFlagAttributes(this->attribute_list_);

    this->AddAttribute("title",    &this->title_);
    this->AddAttribute("position", &this->position_overwrite_);
    this->AddAttribute("size",     &this->size_overwrite_);
    this->AddAttribute("padding",  &this->padding_);
}

void Panel::IMPL_Update(Float2 position, Float2 size)
{
    if (this->init_position_and_size_)
        this->InitPositionAndSize(position, size);

    if (this->style_)
        this->style_->PushStyle();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin(this->title_, 0, this->GenerateWindowFlags()))
    {
        if (this->style_)
            this->style_->PopStyle();

        ImGui::PopStyleVar(1);
        ImGui::End();
        return;
    }

    if (this->style_)
        this->style_->PopStyle();

    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

    Float2 child_size = Float2(
        this->size_.x.value - this->padding_.x.value * 2,
        this->size_.y.value - this->padding_.y.value * 2);

    Float2 child_position = Float2(this->padding_.x, this->padding_.y);

    if (!this->no_title_bar_)
    {
        child_position.y += title_bar_height_;
        child_size.y -= title_bar_height_;
    }

    for (auto& child : this->child_items_)
    {
        if (!child)
            continue;

        child->Update(child_position, child_size);
    }

    if (!this->in_view_)
    {
        this->position_ = ImGui::GetWindowPos();
        this->size_ = ImGui::GetWindowSize();
    }

    ImGui::End();

    ImGui::PopStyleVar(1);
}

void Panel::InitPositionAndSize(Float2 position, Float2 size)
{
    this->position_ = this->position_overwrite_;
    this->size_ = this->size_overwrite_;

    this->title_bar_height_ = this->CalcTitleBarHeight();

    if (this->in_view_)
    {
        this->position_ = position;
        this->size_ = size;

        ImGui::SetNextWindowPos(position);
        ImGui::SetNextWindowSize(size);

        return;
    }

    ImGui::SetNextWindowPos(this->position_);
    ImGui::SetNextWindowSize(this->size_);

    this->init_position_and_size_ = false;
}

float Panel::CalcTitleBarHeight() const
{
    ImGuiStyle& style = ImGui::GetStyle();

    return ImGui::GetFontSize() + style.FramePadding.y * 2.0f;
}

bool Panel::OnProcessStart(std::string& error_message)
{
    ItemBase* parent = this->parent_;

    while (parent)
    {
        if (parent->GetCategory() == ItemCategory::kView)
            this->in_view_ = true;

        parent = parent->GetParent();
    }

    return true;
}

bool Panel::OnProcessEnd(std::string& error_message)
{
    if (!this->in_view_)
    {
        // Make sure that the position and size is set if the panel isn't placed
        // inside a view.
        if (!this->size_overwrite_.value_changed_ ||
            !this->position_overwrite_.value_changed_)
        {
            error_message = "Attribute \"position\" and \"size\" must be "
                            "set when the panel is placed outside of a view.";

            return false;
        }
    }

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
        error_message = "Object of type \"Panel\" can only contain one "
                        "drawable object\".";

        return false;
    }

    this->title_.value += "##" + this->draw_id_;

    return true;
}

Bool Panel::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool Panel::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal
