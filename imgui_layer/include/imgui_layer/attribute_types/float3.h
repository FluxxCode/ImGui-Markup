#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float.h"
#include "imgui_layer/attribute_types/string.h"

#include <string>

namespace gui
{

class Float3 : public Attribute
{
public:
    Float3();
    Float3(float x, float y, float z);

    Float x = 0;
    Float y = 0;
    Float z = 0;

    std::string ToString() const;

    inline bool operator==(const Float3& right) const
    {
        if (right.x == x && right.y == y && right.z == z)
            return true;
        return false;
    }
    inline bool operator!=(const Float3& right) const
    {
        return !(*this == right);
    }

private:
    bool IMPL_LoadValue(const Float3& value);
    bool IMPL_LoadValue(const String& value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT3_H_
