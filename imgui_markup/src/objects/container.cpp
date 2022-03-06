#include "impch.h"
#include "objects/container.h"

namespace imgui_markup::internal
{

Container::Container(std::string id, ObjectBase* parent)
    : ObjectBase("Container", id, parent)
{ }

Container& Container::operator=(const Container& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Container::IMPL_Update()
{
    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->SetPosition(ImGui::GetCursorPos(), Float2(
            this->global_position_.x - this->draw_position_.x,
            this->global_position_.y - this->draw_position_.y));

        child->Update();
    }
}

bool Container::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
        return true;

    error_message = "Object of type \"Container\" can only be created within "
                    "the global file scope";

    return false;
}

}  // namespace imgui_markup::internal
