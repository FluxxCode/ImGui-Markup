#include "impch.h"
#include "objects/attribute_types/object_int.h"

namespace imgui_markup::internal{

ObjectInt::ObjectInt(std::string id, ObjectBase* parent)
    : ObjectBase("Int", id, parent)
{
    this->AddAttribute("value", &this->value);
}

ObjectInt& ObjectInt::operator=(const ObjectInt& other)
{
    for (auto& child : this->child_objects_)
        child->SetParent(other.parent_);

    return *this;
}

}  // namespace imgui_markup::internal