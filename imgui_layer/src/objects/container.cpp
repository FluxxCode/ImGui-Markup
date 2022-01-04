#include "ilpch.h"
#include "imgui_layer/objects/container.h"

namespace gui
{

Container::Container(std::string id, Object* parent)
    : Object("Container", id, parent)
{
    this->RemoveAttribute("position");
    this->RemoveAttribute("size");
}

void Container::Update()
{
    this->UpdateChilds();
}

}  // namespace gui
