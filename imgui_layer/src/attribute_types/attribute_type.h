#ifndef IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
#define IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_

#include "parser/parser_error.h"

#include <string>

namespace gui
{

class AttributeType
{
public:
    // Functions
    bool LoadValue(std::string value);
    virtual bool IMPLLoadValue(std::string value) = 0;

    virtual std::string ToString() = 0;

    bool value_changed_ = false;

    ParserError GetLastError() const;

protected:
    // Variables
    ParserError last_error_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_ATTRIBUTE_TYPES_ATTRIBUTE_TYPE_H_
