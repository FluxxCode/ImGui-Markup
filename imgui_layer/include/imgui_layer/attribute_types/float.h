#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES

#include "imgui_layer/attribute_types/attribute_type.h"

#include <string>

namespace gui
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
    bool IMPL_LoadValue(std::string value);
};

}

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES
