#ifndef IMGUI_MARKUP_SRC_OTHER_BOOL_H_
#define IMGUI_MARKUP_SRC_OTHER_BOOL_H_

#include "attribute_types/attribute_base.h"
#include "attribute_types/string.h"

#include <string>

namespace imgui_markup::internal
{

class Bool : public AttributeBase
{
public:
    Bool();
    Bool(const bool b);

    bool value = true;

    std::string ToString() const;

    inline operator bool() const { return value; }

private:
    bool IMPL_LoadValue(const Bool& value);
    bool IMPL_LoadValue(const String& value);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_BOOL_H_
