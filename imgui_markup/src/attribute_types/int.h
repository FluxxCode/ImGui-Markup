#ifndef IMGUI_MARKUP_SRC_OTHER_INT_H_
#define IMGUI_MARKUP_SRC_OTHER_INT_H_

#include "attribute_types/attribute_base.h"
#include "string.h"

#include <string>

namespace igm::internal
{

class Int : public AttributeBase
{
public:
    Int();
    Int(int i);

    int value = 0;

    std::string ToString() const;

    inline operator int() const { return value; }

private:
    bool IMPL_LoadValue(const Int& value);
    bool IMPL_LoadValue(const String& value);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_INT_H_
