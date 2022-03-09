#include "impch.h"
#include "objects/attribute_types/object_float4.h"

namespace imgui_markup::internal
{

ObjectFloat4::ObjectFloat4(std::string id, ObjectBase* parent)
    : ObjectBase(ObjectType::kObjectFloat4, id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
