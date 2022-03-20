#ifndef IMGUI_MARKUP_SRC_OTHER_REFERENCE_H_
#define IMGUI_MARKUP_SRC_OTHER_REFERENCE_H_

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class Reference : public AttributeBase
{
public:
    Reference(AttributeType expected_type);
    Reference(AttributeBase* reference);

    virtual ~Reference();

    AttributeBase* reference = nullptr;
    AttributeType expected_type = AttributeType::kUndefined;

    std::string ToString() const;

    template<typename T>
    void SetValue(T value)
    {
        if (!this->reference)
            return;

        // Ensure that the expected attribute type matches the attribute type
        // of this reference
        if (this->reference->type_ != value.type)
            return;

        this->reference->LoadValue(value);
    }

private:
    bool IMPL_LoadValue(const Reference& value);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_REFERENCE_H_
