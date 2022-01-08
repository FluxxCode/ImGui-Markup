#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_

#include "imgui_markup/attribute_types/attribute_type.h"
#include "imgui_markup/attribute_types/string.h"

#include <string>

namespace imgui_markup
{

class Bool : public Attribute
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

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_BOOL_H_
