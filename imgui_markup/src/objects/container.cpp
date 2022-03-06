#include "impch.h"
#include "objects/container.h"

namespace imgui_markup::internal{

Container::Container(std::string id, ObjectBase* parent)
    : ObjectBase("Container", id, parent)
{ }

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

}  // namespace imgui_markup::internal