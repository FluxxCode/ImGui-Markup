#include "ilpch.h"
#include "objects/text.h"

namespace gui
{

Text::Text(std::string id, Object* parent)
    : Object("Text", id, parent)
{
    this->AddAttribute("text", &this->text_);
    this->AddAttribute("color", &this->color_);

    this->RemoveAttribute("size");
}

void Text::Update()
{
    if (this->pos_.value_changed_)
        ImGui::SetCursorPos(this->pos_);

    if (this->color_.value_changed_)
        ImGui::TextColored(this->color_, this->text_);
    else
        ImGui::Text(this->text_);
}

}  // namespace gui
