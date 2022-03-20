#ifndef IMGUI_MARKUP_SRC_OTHER_STRING_H_
#define IMGUI_MARKUP_SRC_OTHER_STRING_H_

// Also includes forward declarions for other attribute types
#include "attribute_types/attribute_base.h"

#include <string>

namespace igm::internal
{

class String : public AttributeBase
{
public:
    String();
    String(std::string str);
    String(const char* str);

    std::string value;

    std::string ToString() const;

    inline operator std::string() const { return value; }
    inline operator const char*() const { return value.c_str(); }

private:
    bool IMPL_LoadValue(const Bool& value);
    bool IMPL_LoadValue(const Float& value);
    bool IMPL_LoadValue(const Float2& value);
    bool IMPL_LoadValue(const Float3& value);
    bool IMPL_LoadValue(const Float4& value);
    bool IMPL_LoadValue(const Int& value);
    bool IMPL_LoadValue(const String& value);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_STRING_H_
