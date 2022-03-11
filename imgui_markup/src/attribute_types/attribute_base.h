#ifndef IMGUI_MARKUP_SRC_OTHER_ATTRIBUTE_BASE_H_
#define IMGUI_MARKUP_SRC_OTHER_ATTRIBUTE_BASE_H_

#include "parser/parser_result.h"

#include <string>

namespace imgui_markup::internal
{

enum class AttributeType
{
    kUndefined,
    kBool,
    kFloat,
    kFloat2,
    kFloat3,
    kFloat4,
    kInt,
    kString,
    kReference,
    kEnum
};

class Bool;
class Float;
class Float2;
class Float3;
class Float4;
class Int;
class String;
class Reference;

class AttributeBase
{
public:
    AttributeBase(AttributeType type);
    virtual ~AttributeBase();

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
    bool LoadValue(const AttributeBase& value);
    bool LoadValue(const Bool& value);
    bool LoadValue(const Float& value);
    bool LoadValue(const Float2& value);
    bool LoadValue(const Float3& value);
    bool LoadValue(const Float4& value);
    bool LoadValue(const Int& value);
    bool LoadValue(const String& value);
    bool LoadValue(const Reference& value);

    /**
     * Converts the attribute value type to a std::string.
     */
    virtual std::string ToString() const = 0;

    /**
     * Adds a reference to the references vector.
     * Used to keep track of every reference pointing to this attribute.
     * This way we can ensure that the references pointing to this attribute
     * are set to nullptr when this attribute is deleted.
     */
    void InitReference(Reference* reference);

    /**
     * Removes every instance of a specify reference from the references
     * vector. This should be called every time a specifc reference
     * gets deleted.
     * Currently the function is only called by the reference destructor.
     */
    void RemoveReference(Reference* reference);

private:
    /**
     * References pointing to this attribute type.
     */
    std::vector<Reference*> references_;

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
    virtual bool IMPL_LoadValue(const String& value) { return false; }
    virtual bool IMPL_LoadValue(const Reference& value);
};

}  // namespace imgui_markup::internal

#endif  // IMGUI_MARKUP_SRC_OTHER_ATTRIBUTE_BASE_H_
