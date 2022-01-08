#include "impch.h"
#include "imgui_markup/objects/container.h"

namespace imgui_markup
{

Container::Container(std::string id, Object* parent)
    : Object("Container", id, parent)
{ }

Container& Container::operator=(const Container& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Container::Update()
{
    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->SetPosition(ImGui::GetCursorPos(), Float2(
            this->global_position_.x - this->draw_position_.x,
            this->global_position_.y - this->draw_position_.y));

        child->Update();

        if (child->GetRelativePosition().x + child->GetSize().x > this->size_.x)
            this->size_.x = child->GetRelativePosition().x + child->GetSize().x;

        if (child->GetRelativePosition().y + child->GetSize().y > this->size_.y)
            this->size_.y = child->GetRelativePosition().y + child->GetSize().y;
    }
}

}  // namespace imgui_markup
