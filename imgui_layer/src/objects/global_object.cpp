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
    this->UpdateChilds();
}

void GlobalObject::Reset()
{
    this->version_.value.clear();
    this->description_.value.clear();
    this->author_.value.clear();
}

}  // namespace gui
