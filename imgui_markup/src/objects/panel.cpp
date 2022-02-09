#include "impch.h"
#include "objects/panel.h"

#include "utility/imgui_conversion.h"
#include "objects/panel_style.h"

namespace imgui_markup::internal
{

Panel::Panel(std::string id, ObjectBase* parent)
    : ObjectBase("Panel", id, parent)
{
    this->InitWindowFlagAttributes(this->attribute_list_);

    this->AddAttribute("title",    &this->title_);
    this->AddAttribute("position", &this->global_position_);
    this->AddAttribute("size",     &this->size_);
}

Panel& Panel::operator=(const Panel& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Panel::Update()
{
    if (this->init_panel_attributes_)
        this->InitPanelAttributes();

    if (this->style_)
        this->style_->PushStyle();

    if (!ImGui::Begin(this->title_, 0, this->GenerateWindowFlags()))
    {
        if (this->style_)
            this->style_->PopStyle();

        this->size_ = Float2();

        ImGui::End();
        return;
    }

    if (this->style_)
        this->style_->PopStyle();

    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

    this->size_ = ImGui::GetWindowSize();
    this->global_position_ = ImGui::GetWindowPos();

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->SetPosition(ImGui::GetCursorPos(), this->global_position_);
        child->Update();
    }

    ImGui::End();
}

void Panel::InitPanelAttributes()
{
    if (this->global_position_.value_changed_)
        ImGui::SetNextWindowPos(this->global_position_);
    if (this->size_.value_changed_)
        ImGui::SetNextWindowSize(this->size_);

    this->init_panel_attributes_ = false;
}

bool Panel::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
        return true;

    error_message = "Object of type \"Panel\" can only be created inside the "
                    "global file scope";

    return false;
}

bool Panel::OnProcessEnd(std::string& error_message)
{
    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

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
