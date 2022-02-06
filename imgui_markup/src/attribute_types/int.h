#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_H_

#include "attribute_type.h"
#include "string.h"

#include <string>

namespace imgui_markup
{

class Int : public Attribute
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

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_H_
