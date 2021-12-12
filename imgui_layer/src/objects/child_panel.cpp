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
    if (this->init_)
        this->Init();

    if (this->position_.value_changed_)
        ImGui::SetCursorPos(this->position_);

    if (this->position_.value_changed_)
        ImGui::SetNextWindowSize(this->size_);

    ImGui::BeginChild(this->title_, this->size_, this->border_.value);

    this->UpdateChilds();

    ImGui::EndChild();
}

void ChildPanel::Init()
{
    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

    this->init_ = false;
}

}  // namespace gui
