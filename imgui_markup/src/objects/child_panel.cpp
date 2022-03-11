#include "impch.h"
#include "objects/child_panel.h"

#include "utility/imgui_conversion.h"

namespace imgui_markup::internal
{

ChildPanel::ChildPanel(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kChildPanel, id, parent)
{
    this->AddAttribute("size",   &this->size_overwrite_);
    this->AddAttribute("title",  &this->title_);
    this->AddAttribute("border", &this->border_);
}

void ChildPanel::IMPL_Update(Float2 position, Float2 size)
{
    this->position_ = position;
    this->size_ = size;

    ImGui::SetCursorPos(position);

    ImGui::BeginChild(
        this->title_,
        this->size_overwrite_.value_changed_ ? this->size_overwrite_ : size,
        this->border_.value);

    this->is_hovered_ = ImGui::IsWindowHovered();

    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update(ImGui::GetCursorPos());
    }

    if (size == Float2(0, 0))
        this->size_ = ImGui::GetWindowSize();

    ImGui::EndChild();
}

bool ChildPanel::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ObjectType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the child panels parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

bool ChildPanel::OnProcessEnd(std::string& error_message)
{
    if (this->title_.value.empty())
        this->title_ = "##" + this->draw_id_;

    return true;
}

Bool ChildPanel::API_IsPressed(MouseButton button) const
{
    return this->is_hovered_&&
        ImGui::IsMouseClicked(MouseButtonToImGui(button));
}

Bool ChildPanel::API_IsHovered() const
{
    return this->is_hovered_;
}

}  // namespace imgui_markup::internal
