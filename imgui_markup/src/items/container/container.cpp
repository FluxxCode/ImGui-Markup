#include "impch.h"
#include "items/container/container.h"

namespace imgui_markup::internal
{

Container::Container(std::string id, ItemBase* parent)
    : ContainerBase(ItemType::kContainer, id, parent)
{ }

void Container::IMPL_Update(Float2 position, Float2 size)
{
    this->position_ = position;
    this->size_ = size;

    for (auto& child : this->child_items_)
    {
        if (!child)
            continue;

        child->Update(position, size);
    }
}

bool Container::OnProcessStart(std::string& error_message)
{
    if (!this->parent_)
        return true;

    error_message = "Item of type \"Container\" can only be created within "
                    "the global file scope";

    return false;
}

}  // namespace imgui_markup::internal
