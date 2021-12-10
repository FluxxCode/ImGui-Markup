#ifndef IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_
#define IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_

#include "parser/parser.h"

#include "imgui_layer/objects/global_object.h"

namespace gui
{

class Interpreter
{
public:
    // Constructor
    /**
     * @param[in] nodes - The nodes that the interpreter will process.
     * @param[in] data   - The raw data that is processed, used for the
     *                     error messages.
    */
    explicit Interpreter(
        const std::vector<std::shared_ptr<Node>> nodes,
        const std::string& data);

    // Functions
    /**
     * Create a global object based on the nodes that where given to the
     * interpreter by the constructor. The global object contains every
     * global attribute and every child object with the loaded attributes based
     * on the nodes.
     *
     * @param[out] global_object - the generated global object.
     *
     * @return true on success, false if there was an error.
    */
    bool CreateGlobalObject(GlobalObject& global_object);

    ParserError GetLastError() const;

private:
    // Variables
    const std::vector<std::shared_ptr<Node>> nodes_;
    GlobalObject global_object_ = GlobalObject();

    mutable ParserError last_error_;
    const std::string& data_;

    // Functions
    /**
     * Set the value of an attribute from the current object based on
     * the current attribute node.
     *
     * @param[out] object - The current object that contains the attribute
     *                      that will be updated.
     * @param[in] attribute_node - The attribute node, containing the name
     *                             and value of the attribute that will
     *                             be updated. If the value is of the
     *                             TokenType kData, the function will get
     *                             the value from a different attribute
     *                             and/or object.
     *
     * @return true if the attribute could be updated successfully,
     *         false if there was an error. The possible errors are:
     *             - There is no attribute with the given name
     *             - The value is of the type kData and the function
     *               was not able to get the value of a different attribute or
     *               object. This can happen, if the attribute or object
     *               does not exists.
     *              - If there was an error when converting the value to the
     *                attribute type.
    */
    bool SetAttribute(
        Object* object,
        std::shared_ptr<Node> attribute_node);

    /**
     * Get the value of an attribute from the given object or the value
     * of an attribute from an object that is already loaded in
     * the global_object_.
     *
     * @param[in] attribute_name - The name of the attribute from where the
     *                             value will be returned.
     * @param[out] destination   - A string that will recive the value of the
     *                             attribute converted to a string.
     * @param[in] object         - The start object that will be checked for
     *                             the attribute. If the object does not
     *                             contain the attribute, the function will
     *                             check any other object that is already
     *                             loaded in the global_object_.
     * @param[in] node           - The current node that is processed,
     *                             used for error messages.
    */
    bool GetAttribute(
        std::string attribute_name,
        std::string& destination,
        Object* object,
        std::shared_ptr<Node> node) const;

    /**
     * Create a child object based on the current object node and load
     * the attributes and other child objects from the object that will be
     * created.
     *
     * @param[in] parent - The parent object of the object that will
     *                     be created.
     * @param[in] object_node - The object node that is used to create
     *                          the object.
     *
     * @return true if there was no error while creating the object,
     *         false if there was an error. The possible errors are:
     *              - The type of the object does not exists
     *                in the object_list.
     *              - There was an error while loading attributes or
     *                child objects of the object that was created.
    */
    bool CreateChildObject(
        Object* parent,
        std::shared_ptr<Node> object_node);

    bool DataIsBool(const std::string str) const;
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_INTERPRETER_H_
