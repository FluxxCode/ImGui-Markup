#include "impch.h"
#include "objects/attribute_types/object_float.h"

namespace imgui_markup::internal
{

ObjectFloat::ObjectFloat(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kObjectFloat, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
