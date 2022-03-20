#include "impch.h"
#include "parser/parser_nodes.h"

namespace igm::internal::parser
{

ParserNode::ParserNode(ParserNodeType type, ParserPosition position)
    : type(type), position(position)
{ }

ParserItemNode::ParserItemNode(
    std::string item_type,
    std::string item_id,
    ParserPosition position)
    : ParserNode(ParserNodeType::kItemNode, position),
      item_type(item_type), item_id(item_id)
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

}  // namespace igm::internal::parser
