#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_

#include "imgui_markup/attribute_types/attribute_type.h"
#include "imgui_markup/attribute_types/string.h"

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

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_INT_H_
