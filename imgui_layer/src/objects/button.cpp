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
    this->PushStyle();

    if (ImGui::Button(this->text_, this->size_))
        this->is_pressed_ = true;
    else
        this->is_pressed_ = false;

    this->PopStyle();
}

bool Button::IsPressed()
{
    return this->is_pressed_;
}

void Button::PushStyle()
{
    if (this->color_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, this->color_);
        this->style_count_++;
    }

    if (this->color_active_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, this->color_active_);
        this->style_count_++;
    }

    if (this->color_hovered_.value_changed_)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, this->color_hovered_);
        this->style_count_++;
    }
}

void Button::PopStyle()
{
    ImGui::PopStyleColor(this->style_count_);
    this->style_count_ = 0;
}

}  // namespace gui
