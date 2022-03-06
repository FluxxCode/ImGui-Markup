#include "impch.h"
#include "objects/attribute_types/object_bool.h"

namespace imgui_markup::internal
{

ObjectBool::ObjectBool(std::string id, ObjectBase* parent)
    : ObjectBase("Bool", id, parent)
{
    this->AddAttribute("value", &this->value);
}

}  // namespace imgui_markup::internal
