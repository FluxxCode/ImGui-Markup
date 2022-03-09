#include "impch.h"
#include "objects/attribute_types/object_string.h"

namespace imgui_markup::internal
{

ObjectString:: ObjectString(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kObjectString, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
