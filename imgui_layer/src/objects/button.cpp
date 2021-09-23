#include "ilpch.h"
#include "objects/button.h"

namespace gui
{

Button::Button(std::string id, Object* parent)
    : Object("Button", id, parent)
{
    this->attribute_list_ = {
        { "size",          &this->size_          },
        { "color",         &this->color_         },
        { "color_active",  &this->color_active_  },
        { "color_hovered", &this->color_hovered_ },
        { "text",          &this->text_          },
    };
}

void Button::Update()
{ }

}  // namespace gui
