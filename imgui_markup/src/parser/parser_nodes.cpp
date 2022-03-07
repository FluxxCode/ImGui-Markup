#include "impch.h"
#include "parser/parser_nodes.h"

namespace imgui_markup::internal::parser
{

ParserNode::ParserNode(ParserNodeType type, ParserPosition position)
    : type(type), position(position)
{ }

ParserObjectNode::ParserObjectNode(
    std::string object_type,
    std::string object_id,
    ParserPosition position)
    : ParserNode(ParserNodeType::kObjectNode, position),
      object_type(object_type), object_id(object_id)
{ }

ParserStringNode::ParserStringNode(
    std::string value,
    ParserPosition position)
    : ParserNode(ParserNodeType::kStringNode, position),
      value(value)
{ }

ParserIntNode::ParserIntNode(
    std::string value,
    ParserPosition position)
    : ParserNode(ParserNodeType::kIntNode, position),
      value(value)
{ }

ParserFloatNode::ParserFloatNode(
    std::string value,
    ParserPosition position)
    : ParserNode(ParserNodeType::kFloatNode, position),
      value(value)
{ }

ParserBoolNode::ParserBoolNode(
    std::string value,
    ParserPosition position)
    : ParserNode(ParserNodeType::kBoolNode, position),
      value(value)
{ }

ParserVectorNode::ParserVectorNode(
    ParserPosition position)
    : ParserNode(ParserNodeType::kVectorNode, position)
{ }

ParserAttributeAssignNode::ParserAttributeAssignNode(
    std::string attribute_name,
    std::shared_ptr<ParserNode> value_node,
    ParserPosition position)
    : ParserNode(ParserNodeType::kAttributeAssignNode, position),
      attribute_name(attribute_name), value_node(value_node)
{ }

ParserAttributeReferenceNode::ParserAttributeReferenceNode(
    std::string attribute_name,
    ParserPosition position)
    : ParserNode(ParserNodeType::kAttributeReferenceNode, position),
      attribute_name(attribute_name)
{ }

}  // namespace imgui_markup::internal::parser
