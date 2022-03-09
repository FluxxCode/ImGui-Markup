#include "impch.h"
#include "objects/attribute_types/object_float3.h"

namespace imgui_markup::internal
{

ObjectFloat3::ObjectFloat3(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kObjectFloat3, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
