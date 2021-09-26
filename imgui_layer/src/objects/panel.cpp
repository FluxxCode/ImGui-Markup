#include "ilpch.h"
#include "objects/panel.h"

namespace gui
{

Panel::Panel(std::string id, Object* parent)
    : Object("Panel", id, parent)
{
    this->attribute_list_ = {
        { "size", &this->size_   },
        { "pos", &this->pos_     },
        { "title", &this->title_ }
    };
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
    ImGui::SetNextWindowPos(this->pos_);
    ImGui::SetNextWindowSize(this->size_);

    this->init_ = false;
}

}  // namespace gui
