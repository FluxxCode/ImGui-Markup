#include "impch.h"
#include "imgui_markup/objects/child_panel.h"

namespace imgui_markup
{

ChildPanel::ChildPanel(std::string id, Object* parent)
    : Object("ChildPanel", id, parent)
{
    this->AddAttribute("size",   &this->size_);
    this->AddAttribute("title",  &this->title_);
    this->AddAttribute("border", &this->border_);
}

ChildPanel& ChildPanel::operator=(const ChildPanel& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void ChildPanel::Update()
{
    if (this->size_.value_changed_)
        ImGui::SetNextWindowSize(this->size_);

    ImGui::SetCursorPos(this->draw_position_);

    ImGui::BeginChild(this->title_, this->size_, this->border_.value);

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->SetPosition(ImGui::GetCursorPos(), this->global_position_);

        child->Update();
    }

    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);
    this->size_  = ImGui::GetWindowSize();

    ImGui::EndChild();
}

bool ChildPanel::OnProcessStart(std::string& error_message)
{
    Object* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == "Panel")
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the child panels parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

bool ChildPanel::OnProcessEnd(std::string& error_message)
{
    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

    return true;
}

}  // namespace imgui_markup
