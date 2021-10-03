#ifndef IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_
#define IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_

#include "parser/parser.h"

#include "objects/global_object.h"

namespace gui
{

class Interpreter
{
public:
    // Constructor
    explicit Interpreter(const std::vector<std::shared_ptr<Node>> nodes);

    // Functions
    GlobalObject CreateGlobalObject();

private:
    // Variables
    const std::vector<std::shared_ptr<Node>> nodes_;
    GlobalObject global_object_ = GlobalObject();

    // Functions
    bool SetAttribute(
        Object* object,
        std::shared_ptr<Node> attribute_node);
    bool GetAttribute(
        std::string attribute_name,
        std::string& destination,
        Object* object) const;

    bool CreateChildObject(
        Object* parent,
        std::shared_ptr<Node> object_node);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_
