#include "ilpch.h"
#include "objects/text.h"

namespace gui
{

Text::Text(std::string id, Object* parent)
    : Object("Text", id, parent)
{
    this->attribute_list_ = {
        { "text",  &this->text_  },
        { "pos",   &this->pos_   },
        { "color", &this->color_ }
    };
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
