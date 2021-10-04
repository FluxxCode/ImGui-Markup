#include "ilpch.h"
#include "objects/button.h"

namespace gui
{

Button::Button(std::string id, Object* parent)
    : Object("Button", id, parent)
{
    this->attribute_list_ = {
        { "pos",           &this->pos_           },
        { "size",          &this->size_          },
        { "color",         &this->color_         },
        { "color_active",  &this->color_active_  },
        { "color_hovered", &this->color_hovered_ },
        { "text",          &this->text_          }
    };
}

void Button::Update()
{
    ImGui::PushStyleColor(ImGuiCol_Button,        this->color_);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  this->color_active_);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, this->color_hovered_);

    if (ImGui::Button(this->text_, this->size_))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;

    ImGui::PopStyleColor(3);
}

bool Button::IsPressed()
{
    return this->is_pressed_;
}

}  // namespace gui
