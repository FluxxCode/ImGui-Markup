#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_PARSER_NODES_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_PARSER_NODES_H_

#include "parser/parser_result.h"
#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/int.h"
#include "attribute_types/string.h"

#include <string>
#include <vector>
#include <memory>

namespace imgui_markup::internal::parser
{

enum class ParserNodeType
{
    kRootNode,
    kObjectNode,
    kAttributeAssignNode,
    kStringNode,
    kIntNode,
    kFloatNode,
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

    const String value;
};

struct ParserIntNode : public ParserNode
{
    ParserIntNode(std::string value, ParserPosition position);

    const std::string value;
};

struct ParserFloatNode : public ParserNode
{
    ParserFloatNode(std::string value, ParserPosition position);

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

}  // namespace imgui_markup::internal::parser

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_PARSER_NODES_H_
