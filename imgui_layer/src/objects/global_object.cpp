#include "ilpch.h"
#include "objects/global_object.h"

#include "objects/object_list.h"

namespace gui
{

GlobalObject::GlobalObject()
    : Object("GlobalObject", "global", nullptr)
{
    this->attribute_list_ = {
        { "version", &this->version_},
        { "description", &this->description_},
        { "author", &this->author_}
    };
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
