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
        { "text",          &this->text_          },
    };
}

void Button::Update()
{
    if (ImGui::Button(this->text_.value.c_str(), ImVec2(this->size_.x, this->size_.y)))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;
}

bool Button::IsPressed()
{
    return this->is_pressed_;
}

}  // namespace gui
