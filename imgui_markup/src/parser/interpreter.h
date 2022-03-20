#ifndef IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_INTERPRETER_H_
#define IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_INTERPRETER_H_

#include "parser/parser_result.h"
#include "parser/lexer.h"
#include "parser/parser_nodes.h"
#include "common/file_context.h"
#include "attribute_types/bool.h"
#include "attribute_types/float.h"
#include "attribute_types/float2.h"
#include "attribute_types/float3.h"
#include "attribute_types/float4.h"
#include "attribute_types/int.h"
#include "attribute_types/string.h"
#include "attribute_types/reference.h"
#include "attribute_types/enum.h"

#include <string>
#include <vector>
#include <memory>

namespace igm::internal::parser
{

struct InterpreterException
{
    InterpreterException(
        std::string message, ParserNode node, ParserResultType type)
        : message(message), node(node), type(type)
    { }

    const std::string message;
    const ParserNode node;
    const ParserResultType type;
};

struct ExpectedItemDeclaration : public InterpreterException
{
    ExpectedItemDeclaration(ParserNode node)
        : InterpreterException("Expected item declaration", node,
                               ParserResultType::kExpectedItemDeclaration)
    { }
};

struct WrongBaseNode : public InterpreterException
{
    WrongBaseNode(ParserNode node)
        : InterpreterException("Expected item or attribute definition", node,
                              ParserResultType::kWrongBaseNode)
    { }
};

struct UndefinedItemType : public InterpreterException
{
    UndefinedItemType(ParserNode node)
        : InterpreterException("Undefined item type", node,
                              ParserResultType::kUndefinedItemType)
    { }
};

struct MissingAttributeValue : public InterpreterException
{
    MissingAttributeValue(ParserNode node)
        : InterpreterException("Missing attribute value", node,
                              ParserResultType::kMissingAttributeValue)
    { }
};

struct UnknownAttributeValueType : public InterpreterException
{
    UnknownAttributeValueType(ParserNode node)
        : InterpreterException("Wrong type of attribute value, "
                               "expecting string, number or vector", node,
                              ParserResultType::kUnknownAttributeValueType)
    { }
};

struct AttributeConversionError : public InterpreterException
{
    // This constructor is only used by Interpreter::ThrowReferenceError
    AttributeConversionError(std::string message, ParserNode node)
        : InterpreterException(message, node,
                              ParserResultType::kAttributeConversionError)
    { }

    AttributeConversionError(std::string type_left, std::string type_right,
                             std::string value, ParserNode node)
        : InterpreterException("Unable to convert \"" + value +
                               "\" of type \"" + type_right + "\" to a " +
                               "value of type \"" + type_left + "\"", node,
                              ParserResultType::kAttributeConversionError)
    { }

    AttributeConversionError(std::string type_left,
                             std::string value, ParserNode node)
        : InterpreterException("Unable to convert \"" + value + "\" to a " +
                               "value of type \"" + type_left + "\"", node,
                              ParserResultType::kAttributeConversionError)
    { }
};

struct AttributeDoesNotExists : public InterpreterException
{
    AttributeDoesNotExists(std::string item_type,
                           std::string attribute_name, ParserNode node)
        : InterpreterException("Item of type \"" + item_type +
                               "\" has no attribute called \"" +
                               attribute_name + "\"",
                              node, ParserResultType::kAttributeDoesNotExists)
    { }
};

struct ItemIDAlreadyDefined : public InterpreterException
{
    ItemIDAlreadyDefined(std::string id, ParserNode node)
        : InterpreterException("Item with ID \"" + id +
                               "\" is already defined", node,
                              ParserResultType::kItemIDAlreadyDefined)
    { }
};

struct ItemIDGlobalIsReserved : public InterpreterException
{
    ItemIDGlobalIsReserved(ParserNode node)
        : InterpreterException("Item ID \"global\" is reserved and cant "
                               "be used", node,
                              ParserResultType::kItemIDGlobalIsReserved)
    { }
};

struct InvalidItemID : public InterpreterException
{
    InvalidItemID(std::string item_id, ParserNode node)
        : InterpreterException("Item ID \"" + item_id + "\" is invalid",
                              node, ParserResultType::kItemIsNotDefined)
    { }
};


struct ItemIsNotDefined : public InterpreterException
{
    ItemIsNotDefined(std::string item_id, ParserNode node)
        : InterpreterException("Item with ID \"" + item_id + "\" "
                               "is not defined. Make sure to specify the "
                               "full ID", node,
                              ParserResultType::kItemIsNotDefined)
    { }
};

struct NoAttributeSpecified : public InterpreterException
{
    NoAttributeSpecified(ParserNode node)
        : InterpreterException("Reference to items is not supported", node,
                              ParserResultType::kNoAttributeSpecified)
    { }
};

struct ItemIsNotValid : public InterpreterException
{
    ItemIsNotValid(std::string error_message, ParserNode node)
        : InterpreterException(error_message, node,
                              ParserResultType::kItemIsNotValid)
    { }
};

struct InternalWrongNodeType : public InterpreterException
{
    InternalWrongNodeType(ParserNode node)
        : InterpreterException("Internal error: wrong node type", node,
                              ParserResultType::kInternalWrongNodeType)
    { }
};

/**
 * Class to convert a node tree generated by the parser to the final
 * item tree that can be used in the application.
 * The interpreter is build to work together with the parser
 * and not as a standalone class.
 */
class Interpreter
{
public:
    /**
     * Converts a node tree that was generated by the parser to a tree of
     * item that can be used in the application.
     *
     * @param root_node - Root of the node tree.
     * @param dest - Reference to a FileContext receiving the generated
     *               item tree.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ConvertNodeTree(const std::shared_ptr<ParserNode>& root_node,
                         FileContext& dest);

    /**
     * Resets the entire interpreter so it can be used on a new node tree.
     */
    void Reset();

private:
    /**
     * Stores a reference to every item with an ID.
     * This is used to check if IDs are defined multiple times or to get
     * an attribute value from a different item by its ID.
     *
     * The structure of the buffer is:
     * root_id.child_id.child_id.child_id.item_id
     * Where:
     * root_id   = highest parent item with an ID
     * child_id  = items with an ID between the root item and the
     *             referenced item
     * item_id = ID of the referenced item
     *
     * Example:
     * Panel : panel_0
     * {
     *      ChildPanel : cild_panel
     *      {
     *          ChildPanel
     *          {
     *              Button : button_0 { }
     *          }
     *      }
     * }
     * Will be stored as:
     * "panel_0.child_panel.button_0" -> Button
     */
    std::map<std::string, ItemBase&> item_references_;

    /**
     * Adds the item to the item references.
     * The function also checks that there is no ID defined multiple times.
     * Items without an ID will be skipped.
     *
     * @param item - Item that will be added to the item references.
     * @param node - Parser node of the item, used for error handling.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void InitItemReference(ItemBase& item, const ParserNode& node);

    /**
     * Processes a node and executes its child nodes on the parent_item.
     * If the function encounters an item node, it will create a new
     * child item in the parent item.
     * If the function encounters an attribute assign node, it will
     * change the corresponding attribute of the parent_item
     *
     * @param node - Node that will be processed
     * @param parent_item - The item on where the child nodes
     *                        of the node will be executed.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessNodes(const ParserNode& node, ItemBase& parent_item);

    /**
     * Creates a new child item in the parent item and
     * executes the child nodes of the item node on the newly created
     * item.
     *
     * @param node - The item node that will be executed
     * @param parent_item - The item on where the item node
     *                        will be executed.
     * @param no_parent     - Specifies if the parent of the newly created
     *                        item should be nullptr.
     *                        This is currently only used for the root
     *                        items.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessItemNode(
        const ParserNode& node,
        ItemBase& parent_item,
        bool no_parent = false);

    /**
     * Changes the defined attribute of the parent_item to the
     * defined value.
     * The attribtue name and value is defined by the node.
     *
     * @param node - AttributeBase assign node containing attribute name and value.
     * @param parent_item - The item on where the attribute assign node
     *                        will be executed.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessAttributeAssignNode(
        const ParserNode& node, ItemBase& parent_item);

    /**
     * Converts a string node to its value as a string.
     *
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    String ProcessStringNode(const ParserNode& node) const;

    /**
     * Converts a int node to its value as a string.
     *
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Int ProcessIntNode(const ParserNode& node) const;

    /**
     * Converts a int node to its value as a string.
     *
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Float ProcessFloatNode(const ParserNode& node) const;

    /**
     * Converts a bool node to its value as a string.
     *
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Bool ProcessBoolNode(const ParserNode& node) const;

    /**
     * Converts a vector node to its value as a string that can be used
     * on a vector attribute type.
     * The structure of the return value is:
     * value_a,value_b,value_c
     * Keep in mind that the "()" wount be included in the return value.
     * The child nodes of the vector are the values ​​that make up the vector.
     *
     * @param node - Vector node containing the child values.
     * @param parent_item - Item that is used to resolve attribute
     *                        access nodes.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    std::shared_ptr<AttributeBase> ProcessVectorNode(
        const ParserNode& node, ItemBase& parent_item) const;

    /**
     * Resolves an attribute access node to its value as a string.
     * The attribute name structure is:
     * root_id.child_id.child_id.item_id.attribute_name
     * Example:
     * Panel : panel_0
     * {
     *      Text : text_0
     *      {
     *          text = "Hello from text_0"
     *      }
     *
     *      Text : text_1
     *      {
     *          text = panel_0.text_0.text
     *      }
     * }
     *
     * Note: The full ID has to be specified.
     * "text_0.text" will not work!
     *
     * AttributeBase names without a '.'corresponds to an attribute of the
     * parent item.
     * Example:
     * Panel : panel_0
     * {
     *      pos = (12, 12)
     *      size = position  # position is the attribute of panel_0. No need to
     *                       # specify the full ID.
     * }
     *
     * @param node - AttributeBase access node that will be executed
     * @param parent_item - Parent item that is used for local attribute
     *                        names.
     * @return The value of the references attribute
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Reference ProcessAttributeReferenceNode(
        const ParserNode& node, ItemBase& parent_item) const;

    /**
     * Helper function that takes a node of one of the following types:
     * - StringNode
     * - NumberNode
     * - VectorNode
     * - AttributeAccessNode
     *
     * The function will call the corresponding process function of the node
     * type.
     *
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    std::shared_ptr<AttributeBase> ProcessValueNode(
        const ParserNode& node, ItemBase& parent_item) const;

    /**
     * Gets the attribute value of an item in the item_reference buffer.
     *
     * @param attribute - Full name of the attribute, containing full ID of
     *                    the item. E.g. panel_0.text_0.position
     * @param node - Used for error handling
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    AttributeBase& GetAttribtueFromItemReference(
        const std::string attribute, const ParserNode& node) const;

    /**
     * Gets the full item ID of an attribtue reference string.
     * Uses the item references.
     * Example:
     * item_0.child_0.child_1.attribute -> item_0.chidl_0.child_1
     *
     * The function will also check if the item exists in the
     * item references. An exception is thrown if it does not exists.
     *
     * @param attribute - Full name of the attribute, containing full ID of
     *                    the item. E.g. panel_0.text_0.position
     * @param node - Used for error handling
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    std::string GetItemNameFromAttributeReferenceString(
        const std::string attribute, const ParserNode& node) const;

    /**
     * Helper function to throw a reference error.
     * Should only be called when either attribute or value is an enum.
     */
    void ThrowReferenceError(
        AttributeBase* attribute,
        AttributeBase* value,
        ParserNode& node) const;

    /**
     * Helper function to throw an error when the attribute is an enum.
     */
    void ThrowEnumError(
        AttributeBase* awttribute,
        AttributeBase* value,
        ParserNode& node) const;

    /**
     * Converts the type of an attribtue to one of the following strings:
     *  - "Bool"
     *  - "Float"
     *  - "Float2"
     *  - "Float3"
     *  - "Float4"
     *  - "Int"
     *  - "String"
     *  - "Reference"
     */
    std::string AttributeTypeToString(const AttributeBase& attribute) const;
    std::string AttributeTypeToString(const AttributeType type) const;
};

}  // namespace igm::internal::parser

#endif  // IMGUI_MARKUP_SRC_IMGUI_MARKUP_PARSER_INTERPRETER_H_
