#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_INTERPRETER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_INTERPRETER_H_

#include "imgui_layer/parser/parser_result.h"
#include "imgui_layer/parser/lexer.h"
#include "imgui_layer/parser/parser_nodes.h"
#include "imgui_layer/objects/global_object.h"
#include "imgui_layer/attribute_types/bool.h"
#include "imgui_layer/attribute_types/float.h"
#include "imgui_layer/attribute_types/float2.h"
#include "imgui_layer/attribute_types/float3.h"
#include "imgui_layer/attribute_types/float4.h"
#include "imgui_layer/attribute_types/int.h"
#include "imgui_layer/attribute_types/string.h"

#include <string>
#include <vector>
#include <memory>

namespace gui
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

struct WrongBaseNode : public InterpreterException
{
    WrongBaseNode(ParserNode node)
        : InterpreterException("Expected object or attribute definition", node,
                              ParserResultType::kWrongBaseNode)
    { }
};

struct UndefinedObjectType : public InterpreterException
{
    UndefinedObjectType(ParserNode node)
        : InterpreterException("Undefined object type", node,
                              ParserResultType::kUndefinedObjectType)
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
    AttributeConversionError(std::string type_left, std::string type_right,
                             std::string value, ParserNode node)
        : InterpreterException("Unable to convert \"" + value +
                               "\" of type \"" + type_right + "\" to a " +
                               "value of type: \"" + type_left + "\"", node,
                              ParserResultType::kAttributeConversionError)
    { }
    AttributeConversionError(std::string type_left,
                             std::string value, ParserNode node)
        : InterpreterException("Unable to convert \"" + value + "\" to a " +
                               "value of type: \"" + type_left + "\"", node,
                              ParserResultType::kAttributeConversionError)
    { }
};

struct AttributeDoesNotExists : public InterpreterException
{
    AttributeDoesNotExists(std::string object_type, std::string object_id,
                           std::string attribute_name, ParserNode node)
        : InterpreterException("Object of type \"" + object_type +
                               "\" with ID \"" + object_id + "\" has no "
                               "attribute called \"" + attribute_name + "\"",
                              node, ParserResultType::kAttributeDoesNotExists)
    { }
};

struct ObjectIDAlreadyDefined : public InterpreterException
{
    ObjectIDAlreadyDefined(std::string id, ParserNode node)
        : InterpreterException("Object with ID \"" + id +
                               "\" is already defined", node,
                              ParserResultType::kObjectIDAlreadyDefined)
    { }
};

struct ObjectIDGlobalIsReserved : public InterpreterException
{
    ObjectIDGlobalIsReserved(ParserNode node)
        : InterpreterException("Object ID \"global\" is reserved and cant "
                               "be used", node,
                              ParserResultType::kObjectIDGlobalIsReserved)
    { }
};

struct InvalidObjectID : public InterpreterException
{
    InvalidObjectID(std::string object_id, ParserNode node)
        : InterpreterException("Object ID \"" + object_id + "\" is invalid",
                              node, ParserResultType::kObjectIsNotDefined)
    { }
};


struct ObjectIsNotDefined : public InterpreterException
{
    ObjectIsNotDefined(std::string object_id, ParserNode node)
        : InterpreterException("Object with ID \"" + object_id + "\" "
                               "is not defined. Make sure to sepcify the "
                               "full ID", node,
                              ParserResultType::kObjectIsNotDefined)
    { }
};

struct NoAttributeSpecified : public InterpreterException
{
    NoAttributeSpecified(ParserNode node)
        : InterpreterException("Reference to objects is not supported", node,
                              ParserResultType::kNoAttributeSpecified)
    { }
};

struct ObjectIsNotValid : public InterpreterException
{
    ObjectIsNotValid(std::string error_message, ParserNode node)
        : InterpreterException(error_message, node,
                              ParserResultType::kObjectIsNotValid)
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
 * object tree that can be used in the application.
 * The interpreter is build to work together with the parser
 * and not as a standalone class.
 */
class Interpreter
{
public:
    /**
     * Converts a node tree that was generated by the parser to a tree of
     * object that can be used in the application.
     *
     * @param root_node - Root of the node tree.
     * @param dest - Reference to a GlobalObject receiving the generated
     *               object tree.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ConvertNodeTree(const std::shared_ptr<ParserNode>& root_node,
                         GlobalObject& dest);

    /**
     * Resets the entire interpreter so it can be used on a new node tree.
     */
    void Reset();

private:
    /**
     * Stores a reference to every object with an ID.
     * This is used to check if IDs are defined multiple times or to get
     * an attribute value from a different object by its ID.
     *
     * The structure of the buffer is:
     * root_id.child_id.child_id.child_id.object_id
     * Where:
     * root_id   = highest parent object with an ID
     * child_id  = objects with an ID between the root object and the
     *             referenced object
     * object_id = ID of the referenced object
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
    std::map<std::string, Object&> object_references_;

    /**
     * Adds the object to the object references.
     * The function also checks that there is no ID defined multiple times.
     * Objects without an ID will be skipped.
     *
     * @param object - Object that will be added to the object references.
     * @param node - Parser node of the object, used for error handling.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void InitObjectReference(Object& object, const ParserNode& node);

    /**
     * Processes a node and executes its child nodes on the parent_object.
     * If the function encounters an object node, it will create a new
     * child object in the parent object.
     * If the function encounters an attribute assign node, it will
     * change the corresponding attribute of the parent_object
     *
     * @param node - Node that will be processed
     * @param parent_object - The object on where the child nodes
     *                        of the node will be executed.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessNodes(const ParserNode& node, Object& parent_object);

    /**
     * Creates a new child object in the parent object and
     * executes the child nodes of the object node on the newly created
     * object.
     *
     * @param node - The object node that will be executed
     * @param parent_object - The object on where the object node
     *                        will be executed.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessObjectNode(const ParserNode& node, Object& parent_object);

    /**
     * Changes the defined attribute of the parent_object to the
     * defined value.
     * The attribtue name and value is defined by the node.
     *
     * @param node - Attribute assign node containing attribute name and value.
     * @param parent_object - The object on where the attribute assign node
     *                        will be executed.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void ProcessAttributeAssignNode(
        const ParserNode& node, Object& parent_object);

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
     * @param parent_object - Object that is used to resolve attribute
     *                        access nodes.
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    std::shared_ptr<Attribute> ProcessVectorNode(
        const ParserNode& node, Object& parent_object) const;

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
    std::shared_ptr<Attribute> ProcessValueNode(
        const ParserNode& node, Object& parent_object) const;

    /**
     * Resolves an attribute access node to its value as a string.
     * The attribute name structure is:
     * root_id.child_id.child_id.object_id.attribute_name
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
     * Attribute names without a '.'corresponds to an attribute of the
     * parent object.
     * Example:
     * Panel : panel_0
     * {
     *      pos = (12, 12)
     *      size = position  # position is the attribute of panel_0. No need to
     *                       # specify the full ID.
     * }
     *
     * @param node - Attribute access node that will be executed
     * @param parent_object - Parent object that is used for local attribute
     *                        names.
     * @return The value of the references attribute
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Attribute& ProcessAttributeAccessNode(
        const ParserNode& node, Object& parent_object) const;

    /**
     * Gets an attribute from the given object as a string.
     *
     * @param node - Used for error handling
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Attribute& GetAttributeFromObject(
        const std::string attribute,
        Object& parent_object,
        const ParserNode& node) const;

    /**
     * Gets the attribute value of an object in the object_reference buffer.
     *
     * @param attribute - Full name of the attribute, containing full ID of
     *                    the object. E.g. panel_0.text_0.position
     * @param node - Used for error handling
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    Attribute& GetAttribtueFromObjectReference(
        const std::string attribute, const ParserNode& node) const;

    /**
     * Gets the full object ID of an attribtue reference string.
     * Uses the object references.
     * Example:
     * object_0.child_0.child_1.attribute -> object_0.chidl_0.child_1
     *
     * The function will also check if the object exists in the
     * object references. An exception is thrown if it does not exists.
     *
     * @param attribute - Full name of the attribute, containing full ID of
     *                    the object. E.g. panel_0.text_0.position
     * @param node - Used for error handling
     * @throws The function can throw interpreter and std exceptions.
     *         The parser will only catch the interpreter exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    std::string GetObjectNameFromAttributeReferenceString(
        const std::string attribute, const ParserNode& node) const;

    /**
     * Converts the type of an attribtue to one of the following strings:
     *  - "Bool"
     *  - "Float"
     *  - "Float2"
     *  - "Float3"
     *  - "Float4"
     *  - "Int"
     *  - "String"
     */
    std::string AttributeTypeToString(const Attribute& attribute) const;
    std::string AttributeTypeToString(const AttributeType type) const;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_INTERPRETER_H_
