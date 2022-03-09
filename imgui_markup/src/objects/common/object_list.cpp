#include "impch.h"
#include "objects/common/object_list.h"

namespace imgui_markup::internal
{

std::shared_ptr<ObjectBase> ObjectList::CreateObject(
    std::string type,
    std::string id,
    ObjectBase* parent)
{
    return ObjectList::Get().IMPLCreateObject(type, id, parent);
}

bool ObjectList::IsDefined(std::string type, ObjectType* converted_type)
{
    return ObjectList::Get().IMPLIsDefined(type, converted_type);
}

ObjectList& ObjectList::Get()
{
    static ObjectList instance;
    return instance;
}

std::shared_ptr<ObjectBase> ObjectList::IMPLCreateObject(
    std::string type,
    std::string id,
    ObjectBase* parent)
{
    ObjectType converted_type;
    if (this->IsDefined(type, &converted_type))
        return this->object_list_.at(converted_type)(id, parent);

    return nullptr;
}

bool ObjectList::IMPLIsDefined(std::string type, ObjectType* converted_type)
{
    ObjectType temp;

    if (!StringToObjectType(type, temp))
        return false;

    if (this->object_list_.find(temp) == this->object_list_.end())
        return false;

    if (converted_type)
        *converted_type = temp;

    return true;
}

}  // namespace imgui_markup::internal
