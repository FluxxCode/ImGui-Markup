#ifndef IMGUI_LAYER_SRC_PARSER_PARSER_H_
#define IMGUI_LAYER_SRC_PARSER_PARSER_H_

#include "parser/lexer.h"

#include "parser/parser_error.h"

namespace gui
{

/*****************************************************************************/

enum class NodeType : unsigned char
{
    kRootNode,
    kObjectNode,
    kAttributeNode
};

class Node
{
public:
    // Constructor/Destructor
    Node(const NodeType type, const Position pos);
    virtual ~Node();

    // Variables
    const NodeType type_;
    const Position position_;
    std::vector<std::shared_ptr<Node>> child_nodes_;

    // Operators
    std::shared_ptr<Node> operator[](unsigned int i) const;
};

class ObjectNode : public Node
{
public:
    // Constructor
    ObjectNode(const std::string obj_name,
               const std::string id,
               const Position pos);

    ObjectNode(const std::string obj_name, const Position pos);

    // Variables
    const std::string name_;
    const std::string id_;
};

class AttributeNode : public Node
{
public:
    // Constructor
    AttributeNode(const std::string name,
                  const std::string value,
                  const TokenType value_type,
                  const Position pos);

    // Variables
    const std::string name_;
    const std::string value_;
    const TokenType value_type_;
};

/*****************************************************************************/

class Parser
{
public:
    // Constructor
    /**
     * @param[in] tokens - The tokens that the parser will process.
     * @param[in] data   - The raw data that is processed, used for the
     *                     error messages.
    */
    Parser(const std::vector<Token> tokens, const std::string& data);

    // Functions
    /**
     * Generate a tree of nodes based on the tokens that where given to the
     * parser by the constructor.
     *
     * @return a vector of the generated node-tree.
    */
    bool Parse(std::vector<std::shared_ptr<Node>>& nodes);

    /**
     * Print a node-tree to the console.
    */
    static void PrintTree(std::vector<std::shared_ptr<Node>> tree);

    /**
     * Print a node with its child nodes to the console.
    */
    static void PrintNode(std::shared_ptr<Node> node);

    ParserError GetLastError() const;

private:
    // Variables
    const std::vector<Token> tokens_;
    int pos_ = 0;

    ParserError last_error_;
    const std::string& data_;

    // Functions
    bool GetTokenAdvance(Token& token);
    inline Token GetLastToken(int offset = 0);
    inline Token GetCurrentToken(int offset = 0);
    inline Token GetNextToken(int offset = 0);

    bool ProcessTokens(std::shared_ptr<Node> parent_node);
    bool CreateObjectNode(std::shared_ptr<Node> parent_node);
    bool CreateAttributeNode(std::shared_ptr<Node> parent_node);

    bool CurrentNodeIsObject();
    bool CurrentNodeIsAttribute();

    bool CreateArray(std::string& buffer);
    bool CreateVector(std::string& buffer);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_PARSER_H_
