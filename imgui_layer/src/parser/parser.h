#ifndef IMGUI_LAYER_SRC_PARSER_PARSER_H_
#define IMGUI_LAYER_SRC_PARSER_PARSER_H_

#include "parser/lexer.h"

/******************************************************************************
*                             Basic tree idea
*
*               |
*               | - GlobalAttribute
*               | - GlobalAttribute
*               | - GlobalAttribute
*               |
*               |                  |- ObjectAttribute
*               |                  |- ObjectAttribute
*               |                  |- ObjectAttribute
* global_space -| - ObjectDefNode -|
*               |                  |                  | - ObjectAttribute
*               |                  |- ObjectDefNode - | - Object Attribute
*               |                                     |
*               |                                     | - ObjectDefNode
*               |
*               | - ObjectDefNode - |- ObjectAttribute
*               |                   |- ObjectAttribute
*               |
*
******************************************************************************/

namespace gui
{

/*****************************************************************************/

enum class NodeType : unsigned char
{
    kObjectNode,
    kAttributeNode
};

class Node
{
public:
    // Constructor/Destructor
    Node(const NodeType type);
    virtual ~Node();

    // Variables
    const NodeType type_;
    std::vector<std::shared_ptr<Node>> child_nodes_;

    // Operators
    std::shared_ptr<Node> operator[](unsigned int i) const;
};

class ObjectNode : public Node
{
public:
    // Constructor
    ObjectNode(const std::string obj_name, const std::string id = "");

    // Variables
    const std::string name_;
    const std::string id_;
};

class AttributeNode : public Node
{
public:
    // Constructor
    AttributeNode(const std::string name,
                  const std::string value_node);

    // Variables
    const std::string name_;
    const std::string value_;
};

/*****************************************************************************/

class IMGUI_LAYER_API Parser
{
public:
    // Constructor
    Parser(const std::vector<Token> tokens);

    // Functions
    std::vector<std::shared_ptr<Node>> Parse();

    void PrintTree(std::vector<std::shared_ptr<Node>> tree);
    void PrintObject(std::shared_ptr<Node> object);

private:
    // Variables
    const std::vector<Token> tokens_;
    int pos_ = 0;

    // Functions
    bool GetTokenAdvance(Token& token);
    inline Token GetLastToken(int offset = 0);
    inline Token GetCurrentToken(int offset = 0);
    inline Token GetNextToken(int offset = 0);

    bool IsObject();

    std::shared_ptr<Node> CreateObject();
    void CreateObject(std::shared_ptr<Node> node);

    std::shared_ptr<Node> CreateAttribute();
    void CreateAttribute(std::shared_ptr<Node> node);

    std::string CreateArray();
    std::string CreateVector();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_PARSER_H_
