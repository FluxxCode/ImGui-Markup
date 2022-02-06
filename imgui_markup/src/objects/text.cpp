#include "impch.h"
#include "objects/text.h"

namespace imgui_markup::internal{

Text::Text(std::string id, ObjectBase* parent)
    : ObjectBase("Text", id, parent)
{
    this->AddAttribute("text", &this->text_);
    this->AddAttribute("color", &this->color_);
}

Text& Text::operator=(const Text& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void Text::Update()
{
    ImGui::SetCursorPos(this->draw_position_);

    if (this->color_.value_changed_)
        ImGui::TextColored(this->color_, "%s", this->text_.value.c_str());
    else
        ImGui::Text("%s", this->text_.value.c_str());

    this->size_ = ImGui::GetItemRectSize();
}

bool Text::OnProcessStart(std::string& error_message)
{
    ObjectBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == "Panel")
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the texts parent objects must be an object "
                    "of type \"Panel\".";
    return false;
}

}  // namespace imgui_markup::internal