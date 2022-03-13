#include "impch.h"
#include "items/container/panel.h"

#include "utility/imgui_conversion.h"
#include "items/styles/panel_style.h"

namespace imgui_markup::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : ContainerBase(ItemType::kPanel, id, parent)
{
    this->AddAttribute("title",    &this->title_);
    this->AddAttribute("position", &this->position_overwrite_);
    this->AddAttribute("size",     &this->size_overwrite_);
    this->AddAttribute("padding",  &this->padding_);

    // Flags:
    this->AddAttribute("no_title_bar",          &this->no_title_bar_);
    this->AddAttribute("no_resize",             &this->no_resize_);
    this->AddAttribute("no_move",               &this->no_move_);
    this->AddAttribute("no_collapse",           &this->no_collapse_);
    this->AddAttribute("always_auto_resize",    &this->always_auto_resize_);
    this->AddAttribute("no_background",         &this->no_background_);
    this->AddAttribute("no_mouse_inputs",       &this->no_mouse_inputs_);
    this->AddAttribute("no_focus_on_appearing", &this->no_focus_on_appearing_);
    this->AddAttribute("no_nav_inputs",         &this->no_nav_inputs_);
    this->AddAttribute("no_nav_focus",          &this->no_nav_focus_);
    this->AddAttribute("unsaved_document",      &this->unsaved_document_);
    this->AddAttribute("no_nav",                &this->no_nav_);
    this->AddAttribute("no_decoration",         &this->no_decoration_);
    this->AddAttribute("no_inputs",             &this->no_inputs_);
    this->AddAttribute("no_bring_to_front_focus",
        &this->no_bring_to_front_focus_);
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

int Panel::GenerateWindowFlags() const
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;

    if (this->no_title_bar_)
        flags |= ImGuiWindowFlags_NoTitleBar;
    if (this->no_resize_)
        flags |= ImGuiWindowFlags_NoResize;
    if (this->no_move_)
        flags |= ImGuiWindowFlags_NoMove;
    if (this->no_scrollbar_)
        flags |= ImGuiWindowFlags_NoScrollbar;
    if (this->no_scroll_with_mouse_)
        flags |= ImGuiWindowFlags_NoScrollWithMouse;
    if (this->no_collapse_)
        flags |= ImGuiWindowFlags_NoCollapse;
    if (this->always_auto_resize_)
        flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if (this->no_background_)
        flags |= ImGuiWindowFlags_NoBackground;
    if (this->no_mouse_inputs_)
        flags |= ImGuiWindowFlags_NoMouseInputs;
    if (this->horizontal_scrollbar_)
        flags |= ImGuiWindowFlags_HorizontalScrollbar;
    if (this->no_focus_on_appearing_)
        flags |= ImGuiWindowFlags_NoFocusOnAppearing;
    if (this->no_bring_to_front_focus_)
        flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (this->always_vertical_scrollbar_)
        flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
    if (this->always_horizontal_scrollbar_)
        flags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
    if (this->no_nav_inputs_)
        flags |= ImGuiWindowFlags_NoNavInputs;
    if (this->no_nav_focus_)
        flags |= ImGuiWindowFlags_NoNavFocus;
    if (this->unsaved_document_)
        flags |= ImGuiWindowFlags_UnsavedDocument;
    if (this->no_nav_)
        flags |= ImGuiWindowFlags_NoNav;
    if (this->no_decoration_)
        flags |= ImGuiWindowFlags_NoDecoration;
    if (this->no_inputs_)
        flags |= ImGuiWindowFlags_NoInputs;

    return flags;
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
