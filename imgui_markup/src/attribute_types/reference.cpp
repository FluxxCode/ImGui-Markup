#include "impch.h"
#include "attribute_types/reference.h"

namespace imgui_markup::internal
{

Reference::Reference()
    : Attribute(AttributeType::kReference)
{ }

Reference::Reference(AttributeType expected_type)
    : Attribute(AttributeType::kReference),
    expected_type(expected_type)
{ }

Reference::Reference(Attribute* reference)
    : Attribute(AttributeType::kReference),
    reference(reference)
{
    if (!this->reference)
        return;

    this->reference->InitReference(this);
}

Reference::~Reference()
{
    if (!this->reference)
        return;

    this->reference->RemoveReference(this);
}

std::string Reference::ToString() const
{
    if (!this->reference)
        return "null";

    return this->reference->ToString();
}

bool Reference::IMPL_LoadValue(const Reference& value_in)
{
    if (!value_in.reference)
        return false;

    if (value_in.reference->type != this->expected_type)
        return false;

    this->reference = value_in.reference;
    return true;
}

}  // namespace imgui_markup::internal
