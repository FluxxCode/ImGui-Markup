#include "impch.h"
#include "objects/common/object_list.h"

namespace imgui_markup::internal{

std::shared_ptr<Object> ObjectList::CreateObject(
    std::string type,
    std::string id,
    Object* parent)
{
    return ObjectList::Get().IMPLCreateObject(type, id, parent);
}

bool ObjectList::IsDefined(std::string type)
{
    return ObjectList::Get().IMPLIsDefined(type);
}

ObjectList& ObjectList::Get()
{
    static ObjectList instance;
    return instance;
}

std::shared_ptr<Object> ObjectList::IMPLCreateObject(
    std::string type,
    std::string id,
    Object* parent)
{
    if (this->IsDefined(type))
        return this->object_list_.at(type)(id, parent);

    return nullptr;
}

bool ObjectList::IMPLIsDefined(std::string type)
{
    if (this->object_list_.find(type) == this->object_list_.end())
        return false;

    return true;
}

}  // namespace imgui_markup::internal