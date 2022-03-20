#ifndef IMGUI_MARKUP_SRC_OTHER_ENUM_H_
#define IMGUI_MARKUP_SRC_OTHER_ENUM_H_

#include "attribute_types/attribute_base.h"
#include "attribute_types/string.h"

#include "common/enum_conversion.h"

#include <string>

namespace igm::internal
{

struct EnumProto
{
    EnumProto(std::string name)
        : name_(name)
    { }

    const std::string name_;
};

// T: Expecting enum with its ConvertEnum function
//    in enum_conversion.h implemented
template<typename T>
class Enum : public AttributeBase, public EnumProto
{
public:
    Enum(T default_value)
        : AttributeBase(AttributeType::kEnum),
          EnumProto(enums::GetEnumName(value)),
        value(default_value)
    { }

    T value;

    std::string ToString() const
    {
        std::string out = "<undefined>";
        enums::ConvertEnum(this->value, out);
        return out;
    }

    inline operator T() const { return this->value; }

private:
    bool IMPL_LoadValue(const String& value_in)
    {
        return enums::ConvertEnum(value_in, this->value);
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_ENUM_H_
