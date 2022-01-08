#ifndef IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
#define IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_

#include "imgui_markup/objects/common/object.h"

#include "imgui_markup/attribute_types/float4.h"
#include "imgui_markup/attribute_types/float2.h"
#include "imgui_markup/attribute_types/string.h"

namespace imgui_markup
{

class Text : public Object
{
public:
    // Constructor/Destructor
    Text(std::string id, Object* parent);

    Text& operator=(const Text& other);

    // Functions
    void Update();

    String text_;
    Float4 color_;
};

}  // namespace imgui_markup

#endif  // IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
