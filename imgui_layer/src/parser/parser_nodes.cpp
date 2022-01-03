#include "ilpch.h"
#include "imgui_layer/parser/parser_nodes.h"

namespace gui
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

ParserAttributeAccessNode::ParserAttributeAccessNode(
    std::string attribute_name,
    ParserPosition position)
    : ParserNode(ParserNodeType::kAttributeAccessNode, position),
      attribute_name(attribute_name)
{ }

}  // namespace gui
