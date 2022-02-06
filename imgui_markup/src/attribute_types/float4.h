#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT4_H_

#include "attribute_types/attribute_type.h"
#include "attribute_types/float.h"
#include "attribute_types/string.h"

#include <string>

namespace imgui_markup::internal{

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
    bool IMPL_LoadValue(const Float4& value);
    bool IMPL_LoadValue(const String& value);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT4_H_
