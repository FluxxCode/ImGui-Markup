#include "ilpch.h"
#include "objects/panel.h"

namespace gui
{

Panel::Panel(std::string id, Object* parent)
    : Object("Panel", id, parent)
{
    this->AddAttribute("title", &this->title_);
}

void Panel::Update()
{
    if (this->init_)
        this->Init();

    ImGui::Begin(this->title_);

    this->UpdateChilds();

    ImGui::End();
}

void Panel::Init()
{
    ImGui::SetNextWindowPos(this->position_);
    ImGui::SetNextWindowSize(this->size_);

    if (this->title_.value.empty())
        this->title_ = this->id_.empty() ? "unknown" : this->id_;

    this->init_ = false;
}

}  // namespace gui
