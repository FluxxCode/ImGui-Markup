#include "impch.h"
#include "objects/global_object.h"

#include "objects/common/object_list.h"

namespace imgui_markup::internal{

GlobalObject::GlobalObject()
    : Object("GlobalObject", "global", nullptr)
{
    this->AddAttribute("id",          &this->id_);
    this->AddAttribute("version",     &this->version_);
    this->AddAttribute("description", &this->description_);
    this->AddAttribute("author",      &this->author_);
    this->AddAttribute("date",        &this->date_);
}

GlobalObject& GlobalObject::operator=(const GlobalObject& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

void GlobalObject::Update()
{
    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update();
    }
}

void GlobalObject::Reset()
{
    this->version_.value.clear();
    this->description_.value.clear();
    this->author_.value.clear();

    this->child_objects_.clear();
}

bool GlobalObject::IsHovered() const noexcept
{
    for (const auto& child : this->child_objects_)
    {
        if (this->IsHovered(*child.get()))
            return true;
    }

    return false;
}

bool GlobalObject::IsHovered(std::string object_id) const noexcept
{
    Object* object = this->GetObjectReference(object_id);
    if (!object)
        return false;

    return this->IsHovered(*object);
}

bool GlobalObject::IsPressed(ImGuiMouseButton button) const noexcept
{
    for (const auto& child : this->child_objects_)
    {
        if (this->IsHovered(*child.get()) && ImGui::IsMouseClicked(button))
            return true;
    }

    return false;
}

bool GlobalObject::IsPressed(
    std::string object_id, ImGuiMouseButton button) const noexcept
{
    Object* object = this->GetObjectReference(object_id);
    if (!object)
        return false;

    return this->IsHovered(*object) && ImGui::IsMouseClicked(button);
}

Object* GlobalObject::GetObjectReference(std::string object_id) const noexcept
{
    if (this->object_references_.find(object_id) ==
        this->object_references_.end())
    {
        return nullptr;
    }

    return &this->object_references_.at(object_id);
}

bool GlobalObject::IsHovered(const Object& object) const noexcept
{
    return object.IsHovered();
}

}  // namespace imgui_markup::internal