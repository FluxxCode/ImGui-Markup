#ifndef IMGUI_MARKUP_SRC_OTHER_FLOAT2_H_
#define IMGUI_MARKUP_SRC_OTHER_FLOAT2_H_

#include "attribute_types/attribute_base.h"
#include "attribute_types/float.h"
#include "attribute_types/string.h"

#include <string>

namespace igm::internal
{

class Float2 : public AttributeBase
{
public:
    Float2();
    Float2(float x, float y);
    Float2(ImVec2 vec);

    Float x = 0.0f;
    Float y = 0.0f;

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
    bool IMPL_LoadValue(const Float2& value);
    bool IMPL_LoadValue(const String& value);

    void Reset();
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_FLOAT2_H_
