#include "impch.h"
#include "attribute_types/reference.h"

namespace imgui_markup::internal
{

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

    // Init the reference to the referenced attribute to ensure that the
    // reference is set to nullptr when the referenced attribute is deleted.
    this->reference->InitReference(this);
}

Reference::~Reference()
{
    if (!this->reference)
        return;

    // Ensure that the reference to this object is deleted from
    // the object to be referenced.
    this->reference->RemoveReference(this);
}

std::string Reference::ToString() const
{
    if (!this->reference)
        return "<null>";

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
