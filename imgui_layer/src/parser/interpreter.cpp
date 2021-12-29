#include "ilpch.h"
#include "imgui_layer/parser/interpreter.h"

#include "objects/common/object_list.h"

namespace gui
{

/* Interpreter */
void Interpreter::ConvertNodeTree(
    const std::shared_ptr<ParserNode>& root_node, GlobalObject& dest)
{
    this->Reset();

    this->InitObjectReference(dest, *root_node.get());
    this->ProcessNodes(*root_node.get(), dest);
}

void Interpreter::Reset()
{
    this->object_references_.clear();
}

void Interpreter::InitObjectReference(
    Object& object, const ParserNode& node)
{
    if (object.GetID().empty())
        return;

    std::string full_id = object.GetID();

    Object* parent = &object;
    while (parent->HasParent())
    {
        parent = parent->GetParent();

        if (!parent)
            break;
        if (parent->GetID().empty())
            continue;
        if (parent->GetID() == "global")
            continue;

        full_id.insert(0, parent->GetID() + '.');
    }

    if (this->object_references_.find(full_id) !=
        this->object_references_.end())
    {
        throw ObjectIDAlreadyDefined(full_id, node);
    }

    this->object_references_.insert(
        std::pair<std::string, Object&>(full_id, object));
}

void Interpreter::ProcessNodes(
    const ParserNode& node, Object& parent_object)
{
    for (const auto& child : node.child_nodes)
    {
        switch (child->type)
        {
        case ParserNodeType::kObjectNode:
            this->ProcessObjectNode(*child.get(), parent_object);
            break;
        case ParserNodeType::kAttributeAssignNode:
            this->ProcessAttributeAssignNode(*child.get(), parent_object);
            break;
        default:
            throw WrongBaseNode(*child.get());
        }
    }
}

void Interpreter::ProcessObjectNode(
    const ParserNode& node_in, Object& parent_object)
{
    if (node_in.type != ParserNodeType::kObjectNode)
        throw InternalWrongNodeType(node_in);

    ParserObjectNode& node = (ParserObjectNode&)node_in;

    std::shared_ptr<Object> object = ObjectList::CreateObject(
        node.object_type, node.object_id, &parent_object);

    if (!object)
        throw UndefinedObjectType(node);

    parent_object.AddChild(object);

    this->InitObjectReference(*object.get(), node);

    this->ProcessNodes(node_in, *object.get());
}

void Interpreter::ProcessAttributeAssignNode(
    const ParserNode& node_in, Object& parent_object)
{
    if (node_in.type != ParserNodeType::kAttributeAssignNode)
        throw InternalWrongNodeType(node_in);

    ParserAttributeAssignNode& node = (ParserAttributeAssignNode&)node_in;

    const std::string type = parent_object.GetName();
    const std::string id   = parent_object.GetID().empty() ?
                                "null" : parent_object.GetID();

    if (!parent_object.HasAttribute(node.attribute_name))
        throw AttributeDoesNotExists(type, id, node.attribute_name, node);
    if (!node.value_node)
        throw MissingAttributeValue(node);

    std::string value =
        this->ProcessValueNode(*node.value_node.get(), parent_object);

    if (!parent_object.SetAttributeValue(node.attribute_name, value))
    {
        throw UnableToSetAttributeValue(
            parent_object.GetLastError().message_, *node.value_node.get());
    }
}

std::string Interpreter::ProcessStringNode(const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kStringNode)
            throw InternalWrongNodeType(node_in);

    ParserStringNode& node = (ParserStringNode&)node_in;

    return node.value;
}

std::string Interpreter::ProcessNumberNode(const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kNumberNode)
            throw InternalWrongNodeType(node_in);

    ParserNumberNode& node = (ParserNumberNode&)node_in;

    return node.value;
}

std::string Interpreter::ProcessVectorNode(
    const ParserNode& node_in, Object& parent_object) const
{
    if (node_in.type != ParserNodeType::kVectorNode)
            throw InternalWrongNodeType(node_in);

    ParserVectorNode& node = (ParserVectorNode&)node_in;

    std::string value;

    for (const auto& child : node.child_nodes)
    {
        if (!value.empty())
            value += ',';

        value += this->ProcessValueNode(*child.get(), parent_object);
    }

    return value;
}

std::string Interpreter::ProcessAttributeAccessNode(
    const ParserNode& node_in, Object& parent_object) const
{
    if (node_in.type != ParserNodeType::kAttributeAccessNode)
            throw InternalWrongNodeType(node_in);

    ParserAttributeAccessNode& node = (ParserAttributeAccessNode&)node_in;

    std::string attribute = node.attribute_name;

    // We will assume a reference to a attribute of the current object
    // if the attribute name does not contain '.'
    if (attribute.find('.') == std::string::npos)
        return this->GetAttributeFromObject(attribute, parent_object, node);

    return this->GetAttribtueFromObjectReference(attribute, node);
}

std::string Interpreter::ProcessValueNode(
    const ParserNode& node, Object& parent_object) const
{
    switch (node.type)
    {
    case ParserNodeType::kStringNode:
        return this->ProcessStringNode(node);
    case ParserNodeType::kNumberNode:
        return this->ProcessNumberNode(node);
    case ParserNodeType::kVectorNode:
        return this->ProcessVectorNode(node, parent_object);
    case ParserNodeType::kAttributeAccessNode:
        return this->ProcessAttributeAccessNode(node, parent_object);
    default:
        throw UnknownAttributeValueType(node);
    }
}

std::string Interpreter::GetAttributeFromObject(
    const std::string attribute,
    Object& object,
    const ParserNode& node) const
{
    const std::string type = object.GetName();
    const std::string id   = object.GetID().empty() ?
                             "null" : object.GetID();

    if (!object.HasAttribute(attribute))
        throw AttributeDoesNotExists(type, id, attribute, node);

    const AttributeType* att = object.GetAttribute(attribute);
    if (!att)
        throw AttributeDoesNotExists(type, id, attribute, node);

    return att->ToString();
}

std::string Interpreter::GetAttribtueFromObjectReference(
    std::string attribute, const ParserNode& node) const
{
    std::string object_id =
        this->GetObjectNameFromAttributeReferenceString(attribute, node);

    if (object_id.size() >= attribute.size())
        throw NoAttributeSpecified(node);

    attribute = attribute.substr(object_id.size() + 1);

    if (this->object_references_.find(object_id) ==
        this->object_references_.end())
    {
        throw ObjectIsNotDefined(object_id, node);
    }

    Object& object = this->object_references_.at(object_id);

    const std::string type = object.GetName();
    const std::string id   = object.GetID().empty() ?
                                "null" : object.GetID();

    const AttributeType* att = object.GetAttribute(attribute);
    if (!att)
        throw AttributeDoesNotExists(type, id, attribute, node);

    return att->ToString();
}

std::string Interpreter::GetObjectNameFromAttributeReferenceString(
    const std::string attribute, const ParserNode& node) const
{
    if (attribute.size() <= 3)
            throw InvalidObjectID(attribute, node);

    const std::vector<std::string> segments =
        utils::SplitString(attribute, '.');

    if (segments.empty())
        throw InvalidObjectID(attribute, node);

    std::string object_id;
    for (const auto& segment : segments)
    {
        std::string id = object_id;
        if (!id.empty())
            id += '.';

        id += segment;
        if (this->object_references_.find(id) == this->object_references_.end())
            break;

        object_id = id;
    }

    if (this->object_references_.find(object_id) ==
        this->object_references_.end())
    {
        throw ObjectIsNotDefined(object_id, node);
    }

    return object_id;
}

}  // namespace gui
