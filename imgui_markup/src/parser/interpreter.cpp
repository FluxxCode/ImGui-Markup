#include "impch.h"
#include "parser/interpreter.h"

#include "items/item_list.h"

namespace imgui_markup::internal::parser
{

/* Interpreter */
void Interpreter::ConvertNodeTree(
    const std::shared_ptr<ParserNode>& root_node,
    FileContext& dest)
{
    // TODO: Rework function

    this->Reset();

    std::vector<std::shared_ptr<ItemBase>> item_tree;

    for (auto& child : root_node->child_nodes)
    {
        if (child->type != ParserNodeType::kItemNode)
            throw ExpectedItemDeclaration(*child.get());

        ItemBase temp(
            ItemType::kUndefined,
            ItemCategory::kOther,
            "<interpreter_temp>",
            nullptr);

        this->ProcessItemNode(*child.get(), temp, true);

        if (temp.child_items_.size() == 0)
            continue;

        std::shared_ptr<ItemBase> created_item = temp.child_items_[0];
        created_item->parent_ = nullptr;
        item_tree.push_back(created_item);
    }

    dest.item_tree_= item_tree;
    dest.item_references_ = this->item_references_;
}

void Interpreter::Reset()
{
    this->item_references_.clear();
}

void Interpreter::InitItemReference(
    ItemBase& item, const ParserNode& node)
{
    if (item.GetID().empty())
        return;

    std::string full_id = item.GetID();

    ItemBase* parent = &item;
    while (true)
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

    if (this->item_references_.find(full_id) !=
        this->item_references_.end())
    {
        throw ItemIDAlreadyDefined(full_id, node);
    }

    this->item_references_.insert(
        std::pair<std::string, ItemBase&>(full_id, item));
}

void Interpreter::ProcessNodes(
    const ParserNode& node, ItemBase& parent_item)
{
    for (const auto& child : node.child_nodes)
    {
        switch (child->type)
        {
        case ParserNodeType::kItemNode:
            this->ProcessItemNode(*child.get(), parent_item);
            break;
        case ParserNodeType::kAttributeAssignNode:
            this->ProcessAttributeAssignNode(*child.get(), parent_item);
            break;
        default:
            throw WrongBaseNode(*child.get());
        }
    }
}

void Interpreter::ProcessItemNode(
    const ParserNode& node_in, ItemBase& parent_item, bool no_parent)
{
    if (node_in.type != ParserNodeType::kItemNode)
        throw InternalWrongNodeType(node_in);

    ParserItemNode& node = (ParserItemNode&)node_in;

    std::shared_ptr<ItemBase> item = ItemList::CreateItem(
        node.item_type, node.item_id, no_parent ? nullptr : &parent_item);

    if (!item)
        throw UndefinedItemType(node);

    std::string error_message;

    parent_item.AddChild(item);

    this->InitItemReference(*item.get(), node);

    if (!item->OnProcessStart(error_message))
        throw ItemIsNotValid(error_message, node);

    this->ProcessNodes(node_in, *item.get());

    if (!item->OnProcessEnd(error_message))
        throw ItemIsNotValid(error_message, node);
}

void Interpreter::ProcessAttributeAssignNode(
    const ParserNode& node_in, ItemBase& parent_item)
{
    if (node_in.type != ParserNodeType::kAttributeAssignNode)
        throw InternalWrongNodeType(node_in);

    ParserAttributeAssignNode& node = (ParserAttributeAssignNode&)node_in;

    if (!node.value_node)
        throw MissingAttributeValue(node);

    std::shared_ptr<AttributeBase> value =
        this->ProcessValueNode(*node.value_node.get(), parent_item);

    if (!value)
        throw AttributeConversionError("Undefined", "Undefined", node);

    AttributeBase* attribute = parent_item.GetAttribute(node.attribute_name);
    if (!attribute)
    {
        throw AttributeDoesNotExists(
            ItemTypeToString(parent_item.GetType()),
            node.attribute_name, node);
    }

    if (!attribute->LoadValue(*value))
    {
        if (attribute->type_ == AttributeType::kReference ||
            value->type_ == AttributeType::kReference)
        {
            this->ThrowReferenceError(attribute, value.get(), node);
        }
        else if (attribute->type_ == AttributeType::kEnum)
            this->ThrowEnumError(attribute, value.get(), node);

        throw AttributeConversionError(this->AttributeTypeToString(*attribute),
            this->AttributeTypeToString(*value), value->ToString(), node);
    }
}

String Interpreter::ProcessStringNode(
    const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kStringNode)
            throw InternalWrongNodeType(node_in);

    ParserStringNode& node = (ParserStringNode&)node_in;

    return String(node.value);
}

Int Interpreter::ProcessIntNode(
    const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kIntNode)
            throw InternalWrongNodeType(node_in);

    ParserIntNode& node = (ParserIntNode&)node_in;

    Int value;
    if (!value.LoadValue(String(node.value)))
        throw AttributeConversionError("Int", node.value, node_in);

    return value;
}

Float Interpreter::ProcessFloatNode(
    const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kFloatNode)
            throw InternalWrongNodeType(node_in);

    ParserFloatNode& node = (ParserFloatNode&)node_in;

    Float value;
    if (!value.LoadValue(String(node.value)))
        throw AttributeConversionError("Float", node.value, node_in);

    return value;
}

Bool Interpreter::ProcessBoolNode(
    const ParserNode& node_in) const
{
    if (node_in.type != ParserNodeType::kBoolNode)
            throw InternalWrongNodeType(node_in);

    ParserBoolNode& node = (ParserBoolNode&)node_in;

    Bool value;
    if (!value.LoadValue(String(node.value)))
        throw AttributeConversionError("Bool", node.value, node_in);

    return value;
}

std::shared_ptr<AttributeBase> Interpreter::ProcessVectorNode(
    const ParserNode& node_in, ItemBase& parent_item) const
{
    if (node_in.type != ParserNodeType::kVectorNode)
            throw InternalWrongNodeType(node_in);

    ParserVectorNode& node = (ParserVectorNode&)node_in;

    std::string value;
    size_t value_count = 0;

    for (const auto& child : node.child_nodes)
    {
        if (!value.empty())
            value += ',';

        value += this->ProcessValueNode(*child.get(), parent_item)->ToString();

        value_count++;
    }

    if (value_count == 2)
    {
        Float2 final_value;
        if (!final_value.LoadValue(String(value)))
            throw AttributeConversionError("Float2", value, node_in);
        return std::make_shared<Float2>(final_value);
    }
    else if (value_count == 3)
    {
        Float3 final_value;
        if (!final_value.LoadValue(String(value)))
            throw AttributeConversionError("Float3", value, node_in);
        return std::make_shared<Float3>(final_value);
    }
    else if (value_count == 4)
    {
        Float4 final_value;
        if (!final_value.LoadValue(String(value)))
            throw AttributeConversionError("Float4", value, node_in);
        return std::make_shared<Float4>(final_value);
    }

    throw AttributeConversionError("Vector", value, node_in);
}

Reference Interpreter::ProcessAttributeReferenceNode(
    const ParserNode& node_in, ItemBase& parent_item) const
{
    if (node_in.type != ParserNodeType::kAttributeReferenceNode)
            throw InternalWrongNodeType(node_in);

    ParserAttributeReferenceNode& node = (ParserAttributeReferenceNode&)node_in;

    std::string attribute = node.attribute_name;

    AttributeBase* ptr =
        &this->GetAttribtueFromItemReference(attribute, node);

    return Reference(ptr);
}

std::shared_ptr<AttributeBase> Interpreter::ProcessValueNode(
    const ParserNode& node, ItemBase& parent_item) const
{
    switch (node.type)
    {
    case ParserNodeType::kStringNode:
        return std::make_shared<String>(this->ProcessStringNode(node));
    case ParserNodeType::kIntNode:
        return std::make_shared<Int>(this->ProcessIntNode(node));
    case ParserNodeType::kFloatNode:
        return std::make_shared<Float>(this->ProcessFloatNode(node));
    case ParserNodeType::kBoolNode:
        return std::make_shared<Bool>(this->ProcessBoolNode(node));
    case ParserNodeType::kVectorNode:
        return this->ProcessVectorNode(node, parent_item);
    case ParserNodeType::kAttributeReferenceNode:
        return std::make_shared<Reference>(
            this->ProcessAttributeReferenceNode(node, parent_item));
    default:
        throw UnknownAttributeValueType(node);
    }
}

AttributeBase& Interpreter::GetAttribtueFromItemReference(
    std::string attribute, const ParserNode& node) const
{
    std::string item_id =
        this->GetItemNameFromAttributeReferenceString(attribute, node);

    if (item_id.size() >= attribute.size())
        throw NoAttributeSpecified(node);

    attribute = attribute.substr(item_id.size() + 1);

    if (this->item_references_.find(item_id) ==
        this->item_references_.end())
    {
        throw ItemIsNotDefined(item_id, node);
    }

    ItemBase& item = this->item_references_.at(item_id);

    const std::string type = ItemTypeToString(item.GetType());

    AttributeBase* att = item.GetAttribute(attribute);
    if (!att)
        throw AttributeDoesNotExists(type, attribute, node);

    return *att;
}

std::string Interpreter::GetItemNameFromAttributeReferenceString(
    const std::string attribute, const ParserNode& node) const
{
    if (attribute.size() <= 3)
            throw InvalidItemID(attribute, node);

    const std::vector<std::string> segments =
        utils::SplitString(attribute, '.');

    if (segments.empty())
        throw InvalidItemID(attribute, node);

    std::string item_id;
    for (const auto& segment : segments)
    {
        std::string id = item_id;
        if (!id.empty())
            id += '.';

        id += segment;
        if (this->item_references_.find(id) == this->item_references_.end())
        {
            if (item_id.empty())
                item_id = id;
            break;
        }

        item_id = id;
    }

    if (this->item_references_.find(item_id) ==
        this->item_references_.end())
    {
        throw ItemIsNotDefined(item_id, node);
    }

    return item_id;
}

void Interpreter::ThrowReferenceError(
    AttributeBase* attribute,
    AttributeBase* value,
    ParserNode& node) const
{
    AttributeType type_left = attribute->type_;
    AttributeType type_right = value->type_;

    if (type_left == AttributeType::kReference)
    {
        Reference* reference = dynamic_cast<Reference*>(attribute);

        if (type_right != AttributeType::kReference)
        {
            throw AttributeConversionError(
                "Expected reference to an attribute, starting with an '@'",
                node);
        }

        Reference* referenced = dynamic_cast<Reference*>(attribute);

        throw AttributeConversionError(
            "Expected reference to an attribute of type \"" +
            this->AttributeTypeToString(reference->expected_type) + "\"", node);
    }

    Reference* referenced = dynamic_cast<Reference*>(value);

    throw AttributeConversionError(
        this->AttributeTypeToString(type_left),
        this->AttributeTypeToString(referenced->reference->type_),
        referenced->reference->ToString(), node);
}

void Interpreter::ThrowEnumError(
    AttributeBase* attribute,
    AttributeBase* value,
    ParserNode& node) const
{
    if (attribute->type_ != AttributeType::kEnum)
        throw InternalWrongNodeType(node);

    if (value->type_ != AttributeType::kString)
    {
        throw AttributeConversionError(
            "Attribute of type \"Enum\" expects a \"String\" as value", node);
    }

    const std::string name = dynamic_cast<EnumProto*>(attribute)->name_;

    throw AttributeConversionError(
        "Enum of type \"" + name + "\" has no value of \"" +
        value->ToString() + "\"", node);
}

std::string Interpreter::AttributeTypeToString(
    const AttributeBase& attribute) const
{
    return this->AttributeTypeToString(attribute.type_);
}

std::string Interpreter::AttributeTypeToString(const AttributeType type) const
{
    switch (type)
    {
    case AttributeType::kBool:      return "Bool";
    case AttributeType::kFloat:     return "Float";
    case AttributeType::kFloat2:    return "Float2";
    case AttributeType::kFloat3:    return "Float3";
    case AttributeType::kFloat4:    return "Float4";
    case AttributeType::kInt:       return "Int";
    case AttributeType::kString:    return "String";
    case AttributeType::kReference: return "Reference";
    default: return "Undefined";
    }
}

}  // namespace imgui_markup::internal::parser
