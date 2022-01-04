#include "ilpch.h"
#include "imgui_layer/objects/text.h"

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
    if (this->position_.value_changed_)
        ImGui::SetCursorPos(this->position_);

    this->position_ = ImGui::GetCursorPos();

    if (this->color_.value_changed_)
        ImGui::TextColored(this->color_, "%s", this->text_.value.c_str());
    else
        ImGui::Text("%s", this->text_.value.c_str());

    this->size_ = ImGui::GetItemRectSize();
}

}  // namespace gui
