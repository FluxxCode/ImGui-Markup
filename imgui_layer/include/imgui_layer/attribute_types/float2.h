#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_

#include "imgui_layer/attribute_types/attribute_type.h"
#include "imgui_layer/attribute_types/float.h"

#include <string>

namespace gui
{

class Float2 : public Attribute
{
public:
    Float2();
    Float2(float x, float y);
    Float2(ImVec2 vec);

    Float x = 0;
    Float y = 0;

    std::string ToString() const;

    inline operator ImVec2() const { return ImVec2(x, y); }
    inline bool operator==(const Float2& right) const
    {
        if (right.x == x && right.y == y)
            return true;
        return false;
    }
    inline bool operator!=(const Float2& right) const
    {
        return !(*this == right);
    }

private:
    bool IMPL_LoadValue(std::string value);
    void Reset();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_FLOAT2_H_
