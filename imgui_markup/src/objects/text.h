#ifndef IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
#define IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_

#include "objects/common/object_base.h"

#include "attribute_types/float4.h"
#include "attribute_types/float2.h"
#include "attribute_types/string.h"

namespace imgui_markup::internal{

class Text : public ObjectBase
{
public:
    // Constructor/Destructor
    Text(std::string id, ObjectBase* parent);

    Text& operator=(const Text& other);

    // Functions
    void Update();

    String text_;
    Float4 color_;

private:
    // See object.h for documentation
    bool OnProcessStart(std::string& error_message);
};

}  // namespace imgui_markup::internal
#endif  // IMGUI_MARKUP_SRC_OBJECTS_TEXT_H_
