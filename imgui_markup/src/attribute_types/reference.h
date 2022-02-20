#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_REFERENCE_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_REFERENCE_H_

#include "attribute_types/attribute_type.h"

namespace imgui_markup::internal
{

class Reference : public Attribute
{
public:
    Reference();
    Reference(AttributeType expected_type);
    Reference(Attribute* reference);

    virtual ~Reference();

    Attribute* reference = nullptr;
    AttributeType expected_type = AttributeType::kUndefined;

    std::string ToString() const;

private:
    bool IMPL_LoadValue(const Reference& value);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_REFERENCE_H_
