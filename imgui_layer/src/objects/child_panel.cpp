#include "ilpch.h"
#include "imgui_layer/objects/child_panel.h"

namespace gui
{

ChildPanel::ChildPanel(std::string id, Object* parent)
    : Object("ChildPanel", id, parent)
{
    this->AddAttribute("title",  &this->title_);
    this->AddAttribute("border", &this->border_);
}

void ChildPanel::Update()
{
    if (this->position_.value_changed_)
        ImGui::SetCursorPos(this->position_);
    if (this->size_.value_changed_)
        ImGui::SetNextWindowSize(this->size_);

    this->position_ = ImGui::GetCursorPos();

    ImGui::BeginChild(this->title_, this->size_, this->border_.value);

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update();
    }

    this->size_  = ImGui::GetWindowSize();

    ImGui::EndChild();


    ImGui::GetWindowSize();
}

bool ChildPanel::OnProcessEnd(std::string& error_message)
{
    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

    return true;
}

}  // namespace gui
