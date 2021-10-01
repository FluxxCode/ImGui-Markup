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
    if (node_in->type_ != NodeType::kAttributeNode)
        return false;

    AttributeNode* node = dynamic_cast<AttributeNode*>(node_in.get());

    if (node->value_type_ == TokenType::kData)
    {
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

    if (attribute_name.find('.') == std::string::npos)
    {
        // Get the attribute from the start object
        if (!object->HasAttribute(attribute_name))
            return false;

        destination = object->GetAttribute(attribute_name)->ToString();
        return true;
    }

    std::vector<std::string> segments =
        utils::SplitString(attribute_name, '.');

    if (segments[0] == "global")
        segments.erase(segments.begin(), segments.begin() + 1);

    // Get the object with the desired attribute
    Object* obj = (Object*)&this->global_object_;

    // We will skip the last segments, because it is the attribute name itself
    for (unsigned int i = 0; i < segments.size() - 1; i++)
    {
        obj = obj->GetChild(segments[i], true).get();
        if (!obj)
            return false;
    }

    if (!obj)
        return false;

    if (!obj->HasAttribute(segments[segments.size() - 1]))
        return false;

    destination = obj->GetAttribute(segments[segments.size() - 1])->ToString();

    return true;
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

    if (!ObjectList::IsDefined(name))
        return false;

    std::shared_ptr<Object> child = ObjectList::CreateObject(name, id, parent);

    if (!child)
        return false;

    parent->AddChild(child);

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
