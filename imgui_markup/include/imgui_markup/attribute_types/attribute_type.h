#ifndef IMGUI_MARKUP_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_MARKUP_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include "imgui_markup/parser/parser_result.h"

#include <string>

namespace imgui_markup
{

enum class AttributeType
{
    kBool,
    kFloat,
    kFloat2,
    kFloat3,
    kFloat4,
    kInt,
    kString
};

class Bool;
class Float;
class Float2;
class Float3;
class Float4;
class Int;
class String;

class Attribute
{
public:
    Attribute(AttributeType type);

    AttributeType type;

    /**
     * Will be set when the LoadValue function was sucessfully called.
     */
    bool value_changed_ = false;

    /**
     * Loads a string value into the attribute.
     *
     * @param value that will be loaded into the attribute.
     * @return true on sucess
     * @return false if there was a conversion error
     */
    bool LoadValue(const Attribute& value);
    bool LoadValue(const Bool& value);
    bool LoadValue(const Float& value);
    bool LoadValue(const Float2& value);
    bool LoadValue(const Float3& value);
    bool LoadValue(const Float4& value);
    bool LoadValue(const Int& value);
    bool LoadValue(const String& value);

    /**
     * Converts the attribute value type to a std::string.
     */
    virtual std::string ToString() const = 0;

private:
    // NOTE: typename T has to be an imgui_layer attribute!
    template<typename T>
    bool LoadValue(const T& value)
    {
        if (!this->IMPL_LoadValue(value))
            return false;

        this->value_changed_ = true;
        return true;
    }

    virtual bool IMPL_LoadValue(const Bool& value)   { return false; }
    virtual bool IMPL_LoadValue(const Float& value)  { return false; }
    virtual bool IMPL_LoadValue(const Float2& value) { return false; }
    virtual bool IMPL_LoadValue(const Float3& value) { return false; }
    virtual bool IMPL_LoadValue(const Float4& value) { return false; }
    virtual bool IMPL_LoadValue(const Int& value)    { return false; }
    virtual bool IMPL_LoadValue(const String& value) = 0;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_INCLUDE_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
