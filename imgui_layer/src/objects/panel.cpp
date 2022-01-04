#include "ilpch.h"
#include "imgui_layer/objects/panel.h"

namespace gui
{

Panel::Panel(std::string id, Object* parent)
    : Object("Panel", id, parent)
{
    this->AddAttribute("title", &this->title_);
}

void Panel::Update()
{
    if (this->init_panel_attributes_)
        this->InitPanelAttributes();

    ImGui::Begin(this->title_);

    this->size_     = ImGui::GetWindowSize();
    this->position_ = ImGui::GetWindowPos();

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update();
    }

    ImGui::End();
}

void Panel::InitPanelAttributes()
{
    if (this->position_.value_changed_)
        ImGui::SetNextWindowPos(this->position_);
    if (this->size_.value_changed_)
        ImGui::SetNextWindowSize(this->size_);

    this->init_panel_attributes_ = false;
}

bool Panel::Validate(std::string& error_message) const
{
    if (!this->parent_)
        return true;

    if (this->parent_->GetType() == "GlobalObject")
        return true;

    error_message = "Object of type \"Panel\" can only be created inside the global file scope";

    return false;
}

bool Panel::OnProcessEnd(std::string& error_message)
{
    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

    return true;
}

}  // namespace gui
