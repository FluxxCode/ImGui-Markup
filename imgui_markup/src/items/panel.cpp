#include "impch.h"
#include "items/panel.h"

#include "utility/imgui_conversion.h"
#include "items/panel_style.h"

namespace imgui_markup::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kPanel, id, parent)
{
    this->InitWindowFlagAttributes(this->attribute_list_);

    this->AddAttribute("title",    &this->title_);
    this->AddAttribute("position", &this->position_overwrite_);
    this->AddAttribute("size",     &this->size_overwrite_);
}

void Panel::IMPL_Update(Float2 position, Float2 size)
{
    this->position_ = position;
    this->size_ = size;

    if (this->style_)
        this->style_->PushStyle();

    if (this->init_attributes_)
        this->InitAttributes(position, size);

    if (!ImGui::Begin(this->title_, 0, this->GenerateWindowFlags()))
    {
        if (this->style_)
            this->style_->PopStyle();

        ImGui::End();
        return;
    }

    if (this->style_)
        this->style_->PopStyle();

    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

    if (size == Float2(0, 0))
        this->size_ = ImGui::GetWindowSize();

    for (auto& child : this->child_items_)
    {
        if (!child)
            continue;

        child->Update(ImGui::GetCursorPos());
    }

    ImGui::End();
}

void Panel::InitAttributes(Float2 position, Float2 size)
{
    if (this->position_overwrite_.value_changed_)
        ImGui::SetNextWindowPos(this->position_overwrite_);
    else
        ImGui::SetNextWindowPos(position);

    if (this->size_overwrite_.value_changed_)
        ImGui::SetNextWindowSize(this->size_overwrite_);
    else
        ImGui::SetNextWindowSize(size);

    this->init_attributes_ = false;
}

bool Panel::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
        return true;

    error_message = "Item of type \"Panel\" can only be created inside the "
                    "global file scope";

    return false;
}

bool Panel::OnProcessEnd(std::string& error_message)
{
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
