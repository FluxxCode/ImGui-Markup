#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_NODES_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_NODES_H_

#include "imgui_layer/parser/parser_result.h"

#include <string>
#include <vector>
#include <memory>

namespace gui
{

enum class ParserNodeType
{
    kRootNode,
    kObjectNode,
    kAttributeAssignNode,
    kStringNode,
    kNumberNode,
    kBoolNode,
    kVectorNode,
    kAttributeAccessNode
};

struct ParserNode
{
    ParserNode(ParserNodeType type, ParserPosition position);

    const ParserNodeType type;
    ParserPosition position;
    std::vector<std::shared_ptr<ParserNode>> child_nodes;
};

struct ParserObjectNode : public ParserNode
{
    ParserObjectNode(std::string object_type, std::string object_id,
                     ParserPosition position);

    const std::string object_type;
    const std::string object_id;
};

struct ParserStringNode : public ParserNode
{
    ParserStringNode(std::string value, ParserPosition position);

    const std::string value;
};

struct ParserNumberNode : public ParserNode
{
    ParserNumberNode(std::string value, ParserPosition position);

    const std::string value;
};

struct ParserBoolNode : public ParserNode
{
    ParserBoolNode(std::string value, ParserPosition position);

    const std::string value;
};

struct ParserVectorNode : public ParserNode
{
    ParserVectorNode(ParserPosition position);

    // NOTE: Values of the vector are stored in the child nodes.
};

struct ParserAttributeAssignNode : public ParserNode
{
    ParserAttributeAssignNode(std::string attribute_name,
                              std::shared_ptr<ParserNode> value_node,
                              ParserPosition position);

    const std::string attribute_name;
    const std::shared_ptr<ParserNode> value_node;
};

struct ParserAttributeAccessNode : public ParserNode
{
    ParserAttributeAccessNode(std::string attribute_name,
                              ParserPosition position);

    const std::string attribute_name;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_PARSER_NODES_H_
