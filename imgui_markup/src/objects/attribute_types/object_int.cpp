#include "impch.h"
#include "objects/attribute_types/object_int.h"

namespace imgui_markup::internal
{

ObjectInt::ObjectInt(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kObjectInt, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
