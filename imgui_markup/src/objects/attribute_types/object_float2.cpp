#include "impch.h"
#include "objects/attribute_types/object_float2.h"

namespace imgui_markup::internal
{

ObjectFloat2::ObjectFloat2(std::string id, ObjectBase* parent)
    : ObjectBase("Float2", id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
