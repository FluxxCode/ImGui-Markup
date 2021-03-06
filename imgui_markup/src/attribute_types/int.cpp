#include "impch.h"
#include "attribute_types/int.h"

namespace igm::internal
{

Int::Int()
    : AttributeBase(AttributeType::kInt)
{ }

Int::Int(int i)
    : AttributeBase(AttributeType::kInt), value(i)
{ }

std::string Int::ToString() const
{
    return std::to_string(this->value);
}

bool Int::IMPL_LoadValue(const Int& value_in)
{
    this->value = value_in;
    return true;
}

bool Int::IMPL_LoadValue(const String& value_in)
{
    return internal::utils::StringToInt(value_in, &this->value);
}

}  // namespace igm::internal
