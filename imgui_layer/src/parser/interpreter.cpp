#include "ilpch.h"
#include "parser/interpreter.h"

#include "objects/object_list.h"

namespace gui
{

Interpreter::Interpreter(const std::vector<std::shared_ptr<Node>> nodes)
    : nodes_(nodes)
{ }


GlobalObject Interpreter::CreateGlobalObject()
{
    this->global_object_.Reset();

    // Iterate the root nodes, create child objects
    // and load the attributes.
    for (unsigned int i = 0; i < this->nodes_.size(); i++)
    {
        std::shared_ptr<Node> node = this->nodes_[i];
        if (node->type_ == NodeType::kAttributeNode)
            this->SetAttribute(&this->global_object_, node);
        else
            this->CreateChildObject(&this->global_object_, node);
    }

    return this->global_object_;
}

bool Interpreter::SetAttribute(
    Object* object,
    std::shared_ptr<Node> node_in)
{
    // Make sure that the node is an attribute node
    if (node_in->type_ != NodeType::kAttributeNode || !object)
        return false;

    AttributeNode* node = dynamic_cast<AttributeNode*>(node_in.get());

    // If the node type is kData, we expect to get the value from
    // another attribute in the current object or from the attribute in
    // a different object that is already loaded in the global_object_.
    if (node->value_type_ == TokenType::kData)
    {
        // Get the value of a different attribute
        std::string value;
        if (!this->GetAttribute(node->value_, value, object))
            return false;

        return object->SetAttributeValue(node->name_, value);
    }

    return object->SetAttributeValue(node->name_, node->value_);
}

bool Interpreter::GetAttribute(
    std::string attribute_name,
    std::string& destination,
    Object* object) const
{
    if (!object)
        return false;

    // If there is no dot in the name, we will assume that we want
    // the value of an attribute from the current object.
    if (attribute_name.find('.') == std::string::npos)
    {
        if (!object->HasAttribute(attribute_name))
            return false;

        destination = object->GetAttribute(attribute_name)->ToString();
        return true;
    }

    std::vector<std::string> segments =
        utils::SplitString(attribute_name, '.');

    Object* obj = (Object*)&this->global_object_;

    // If the first segment is "global", we will get the value from a
    // attribute that is stored inside the global object.
    if (segments[0] == "global")
    {
        // Make sure that the global object has the attribute.
        // segments[1] is save, as we definitely have a dot in the name,
        // so we will have at least a second segment.
        if (!obj->HasAttribute(segments[1]))
            return false;

        destination = obj->GetAttribute(segments[1])->ToString();
        return true;
    }

    // Iterate every segment and go from object to object and check
    // for an object with the ID of the segment. If we found an object
    // that has the ID specified in the segment, we will go to the next
    // segment and check the child objects for an object with the ID of the
    // segment. We will do this until we have found
    // an attribute that has the name of the next segment.
    // We will skip the last segment, because it has to be the name of
    // the attribute from where we want to get the value.
    for (unsigned int i = 0; i < segments.size() - 1; i++)
    {
        obj = obj->GetChild(segments[i], true).get();

        if (!obj)
            // Object does not have the specified child object
            return false;

        // Check if the object has any attribute with the name of the
        // next segment. i + 1 is save, because we wount get to the last
        // segment in this loop.
        if (obj->HasAttribute(segments[i + 1]))
        {
            destination = obj->GetAttribute(segments[i + 1])->ToString();
            return true;
        }
    }

    // Unable to find any object that has the specified attribute.
    return false;
}

bool Interpreter::CreateChildObject(
    Object* parent,
    std::shared_ptr<Node> object_node)
{
    if (!parent || object_node->type_ != NodeType::kObjectNode)
        return false;

    ObjectNode* node = dynamic_cast<ObjectNode*>(object_node.get());

    std::string name = node->name_;
    std::string id   = node->id_;

    // Make sure that the name (type) is defined in the object list
    if (!ObjectList::IsDefined(name))
        return false;

    // Create a new object on the heap and add it as a child
    // to the parent object.
    std::shared_ptr<Object> child = ObjectList::CreateObject(name, id, parent);

    if (!child)
        return false;

    parent->AddChild(child);

    // Iterate the child nodes, create the child objects
    // and load the attributes into the created object.
    for (unsigned int i = 0; i < object_node->child_nodes_.size(); i++)
    {
        std::shared_ptr<Node> node = object_node->child_nodes_[i];
        if (node->type_ == NodeType::kAttributeNode)
            this->SetAttribute(child.get(), node);
        else
            this->CreateChildObject(child.get(), node);
    }

    return false;
}

}  // namespace gui
