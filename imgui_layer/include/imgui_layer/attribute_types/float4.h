#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float.h"

#include <string>

namespace gui
{

class Float4 : public Attribute
{
public:
    Float4();
    Float4(float x, float y, float z, float w);
    Float4(ImVec4 vec);

    Float x = 0;
    Float y = 0;
    Float z = 0;
    Float w = 0;

    std::string ToString() const;

    inline operator ImVec4() const { return ImVec4(x, y, z, w); }

    inline bool operator==(const Float4& right) const
    {
        if (right.x == x && right.y == y && right.z == z && right.w == w)
            return true;
        return false;
    }
    inline bool operator!=(const Float4& right) const
    {
        return !(*this == right);
    }

private:
    bool IMPL_LoadValue(std::string value);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
