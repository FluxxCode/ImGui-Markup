#include "ilpch.h"
#include "objects/panel.h"

namespace gui
{

Panel::Panel(std::string id, Object* parent)
    : Object("Panel", id, parent)
{
    this->attribute_list_ = {
        {"size", &this->size_},
        {"pos", &this->pos_}
    };
}

void Panel::Update()
{ }

}  // namespace gui
