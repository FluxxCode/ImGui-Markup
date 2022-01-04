#include "ilpch.h"
#include "imgui_layer/objects/global_object.h"

#include "objects/common/object_list.h"

namespace gui
{

GlobalObject::GlobalObject()
    : Object("GlobalObject", "global", nullptr)
{
    this->AddAttribute("id",          &this->id_);
    this->AddAttribute("version",     &this->version_);
    this->AddAttribute("description", &this->description_);
    this->AddAttribute("author",      &this->author_);
    this->AddAttribute("date",        &this->date_);

    this->RemoveAttribute("position");
    this->RemoveAttribute("size");
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

Object* GlobalObject::GetObjectReference(std::string object_id)
{
    if (this->object_references_.find(object_id) ==
        this->object_references_.end())
    {
        return nullptr;
    }

    return &this->object_references_.at(object_id);
}

}  // namespace gui
