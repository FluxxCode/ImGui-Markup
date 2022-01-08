#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "imgui_markup/attribute_types/attribute_type.h"
#include "imgui_markup/attribute_types/string.h"

#include <string>

namespace imgui_markup
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
};

}

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
