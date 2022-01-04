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
    this->position_ = ImGui::GetCursorPos();

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update();

        if (child->position_.x + child->size_.x > this->size_.x)
            this->size_.x = child->position_.x + child->size_.x;

        if (child->position_.y + child->size_.y > this->size_.y)
            this->size_.y = child->position_.y + child->size_.y;
    }
}

}  // namespace gui
