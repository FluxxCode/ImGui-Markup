#include "impch.h"
#include "objects/common/object_mapping.h"

namespace imgui_markup::internal
{

bool StringToObjectType(std::string str, ObjectType& out)
{
    if (object_types::object_mapping.find(str) !=
        object_types::object_mapping.end())
    {
        out = object_types::object_mapping.at(str);
        return true;
    }

    return false;
}

std::string ObjectTypeToString(ObjectType obj)
{
    for (const auto& element : object_types::object_mapping)
    {
        if (element.second == obj)
            return element.first;
    }

    return std::string();
}

}  // namespace imgui_markup::internal
