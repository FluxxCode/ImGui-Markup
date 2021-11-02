#include "ilpch.h"
#include "parser/interpreter.h"

#include "objects/common/object_list.h"

namespace gui
{

Interpreter::Interpreter(
    const std::vector<std::shared_ptr<Node>> nodes,
    const std::string& data)
    : nodes_(nodes), data_(data)
{ }


bool Interpreter::CreateGlobalObject(GlobalObject& global_object)
{
    this->global_object_.Reset();

    // Iterate the root nodes, create child objects
    // and load the attributes.
    for (unsigned int i = 0; i < this->nodes_.size(); i++)
    {
        bool result = false;

        std::shared_ptr<Node> node = this->nodes_[i];
        if (node->type_ == NodeType::kAttributeNode)
            result = this->SetAttribute(&this->global_object_, node);
        else
            result = this->CreateChildObject(&this->global_object_, node);

        if (!result)
            return false;
    }

    global_object = this->global_object_;

    return true;
}

ParserError Interpreter::GetLastError() const
{
    return this->last_error_;
}

bool Interpreter::SetAttribute(
    Object* object,
    std::shared_ptr<Node> node_in)
{
    // Make sure that the node is an attribute node
    if (node_in->type_ != NodeType::kAttributeNode || !object)
    {
        this->last_error_ = ParserError(ParserErrorType::kUndefined,
            "Internal error");

        return false;
    }

    AttributeNode* node = dynamic_cast<AttributeNode*>(node_in.get());

    // If the node type is kData, we expect to get the value from
    // another attribute in the current object or from the attribute in
    // a different object that is already loaded in the global_object_.
    if (node->value_type_ == TokenType::kData)
    {
        // Get the value of a different attribute
        std::string value;
        if (!this->GetAttribute(node->value_, value, object, node_in))
            return false;

        if (!object->SetAttributeValue(node->name_, value))
        {
            this->last_error_ = object->GetLastError();
            this->last_error_ = ParserError(this->last_error_.type_,
                Position(node->position_), this->last_error_.message_,
                this->data_);

            return false;
        }

        return true;
    }

    if (!object->SetAttributeValue(node->name_, node->value_))
    {
        this->last_error_ = object->GetLastError();
        this->last_error_ = ParserError(this->last_error_.type_,
            Position(node->position_), this->last_error_.message_,
            this->data_);

        return false;
    }

    return true;

}

bool Interpreter::GetAttribute(
    std::string attribute_name,
    std::string& destination,
    Object* object,
    std::shared_ptr<Node> node) const
{
    if (!object)
    {
        this->last_error_ = ParserError(ParserErrorType::kUndefined,
            "Internal error");

        return false;
    }

    // If there is not a dot in the name, we will assume that we want
    // the value of an attribute from the current object.
    if (attribute_name.find('.') == std::string::npos)
    {
        if (!object->HasAttribute(attribute_name))
        {
            this->last_error_ = ParserError(
                ParserErrorType::kInvalidAttributeName,
                Position(node->position_),
                "The object \"" + object->GetName() + "\" has no attribute " +
                "called \"" + attribute_name + "\"", this->data_);

            return false;
        }
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
        {
            this->last_error_ = ParserError(
                ParserErrorType::kInvalidAttributeName,
                Position(node->position_),
                "The global object has no attribute called " +
                attribute_name + "\"", this->data_);

            return false;
        }

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
        {
            std::string message = "Unable to find an object with the ID \"" +
                segments[i] + "\".";

            if (i != 0)
            {
                message = "Object \"";

                for (unsigned int x = 0; x < i - 1; x++)
                    message += segments[i];

                message += "\" has no child object with the ID \"" +
                    segments[i] + "\".";
            }

            this->last_error_ = ParserError(
                ParserErrorType::kInvalidObjectID,
                Position(node->position_), message, this->data_);

            return false;
        }

        // Check if the object has any attribute with the name of the
        // next segment. i + 1 is save, because we wount get to the last
        // segment in this loop.
        if (obj->HasAttribute(segments[i + 1]))
        {
            destination = obj->GetAttribute(segments[i + 1])->ToString();
            return true;
        }
    }

    this->last_error_ = ParserError(
        ParserErrorType::kInvalidObjectID,
        Position(node->position_),
        "Unable to find an object with the ID \"" + attribute_name + "\".",
        this->data_);

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
    {
        this->last_error_ = ParserError(
            ParserErrorType::kInvalidObjectID,
            Position(node->position_),
            "Object type \"" + name + "\" is undefined.",
            this->data_);

        return false;
    }

    // Create a new object on the heap and add it as a child
    // to the parent object.
    std::shared_ptr<Object> child = ObjectList::CreateObject(name, id, parent);

    if (!child)
    {
        this->last_error_ = ParserError(
            ParserErrorType::kInvalidObjectID,
            Position(node->position_),
            "Unable to create object of type \"" + name + "\".",
            this->data_);

        return false;
    }

    parent->AddChild(child);

    // Iterate the child nodes, create the child objects
    // and load the attributes into the created object.
    for (unsigned int i = 0; i < object_node->child_nodes_.size(); i++)
    {
        bool result = false;

        std::shared_ptr<Node> node = object_node->child_nodes_[i];
        if (node->type_ == NodeType::kAttributeNode)
            result = this->SetAttribute(child.get(), node);
        else
            result = this->CreateChildObject(child.get(), node);

        if (!result)
            return false;
    }

    return true;
}

}  // namespace gui
