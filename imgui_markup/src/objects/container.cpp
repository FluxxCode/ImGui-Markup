#include "impch.h"
#include "objects/container.h"

namespace imgui_markup::internal
{

Container::Container(std::string id, ObjectBase* parent)
    : ObjectBase("Container", id, parent)
{ }

void Container::IMPL_Update(Float2 position, Float2 size)
{
    for (auto& child : this->child_objects_)
    {
        if (!child)
            continue;

        child->Update(ImGui::GetCursorPos());
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
