#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES

#include "attribute_types/attribute_type.h"
#include "attribute_types/string.h"
#include "attribute_types/int.h"

#include <string>

namespace imgui_markup::internal
{

class Float : public Attribute
{
public:
    Float();
    Float(float f);

    float value = 0;

    std::string ToString() const;

    inline operator float() const { return value; }

private:
    bool IMPL_LoadValue(const Float& value);
    bool IMPL_LoadValue(const String& value);
    bool IMPL_LoadValue(const Int& value);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES
