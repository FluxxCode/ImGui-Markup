#include "ilpch.h"
#include "parser/parser.h"

namespace gui
{

/*****************************************************************************/

Node::Node(const NodeType type, const Position pos)
    : type_(type), position_(pos)
{ }

Node::~Node()
{ }

std::shared_ptr<Node> Node::operator[](unsigned int i) const
{
    return this->child_nodes_[i];
}

ObjectNode::ObjectNode(
    const std::string obj_name,
    const std::string id,
    const Position pos)
    : Node(NodeType::kObjectNode, pos), name_(obj_name), id_(id)
{ }

ObjectNode::ObjectNode(const std::string obj_name, const Position pos)
    : Node(NodeType::kObjectNode, pos), name_(obj_name), id_("")
{ }

AttributeNode::AttributeNode(
    const std::string name,
    const std::string value,
    const TokenType value_type,
    const const Position pos)
    : Node(NodeType::kAttributeNode, pos),
      name_(name), value_(value), value_type_(value_type)
{ }

/*****************************************************************************/

Parser::Parser(const std::vector<Token> tokens)
    : tokens_(tokens)
{ }

std::vector<std::shared_ptr<Node>> Parser::Parse()
{
    std::shared_ptr<Node> root_node = std::make_shared<Node>(
        NodeType::kRootNode, Position(0, 0));

    this->ProcessTokens(root_node);

    return root_node->child_nodes_;
}

void Parser::PrintTree(std::vector<std::shared_ptr<Node>> tree)
{
    for (unsigned int i = 0; i < tree.size(); i++)
    {
        if (tree[i]->type_ == NodeType::kObjectNode)
            Parser::PrintNode(tree[i]);
        else
        {
            AttributeNode* node = dynamic_cast<AttributeNode*>(tree[i].get());
            std::cout << node->name_ << '=' << node->value_ << std::endl;
        }
    }
}

void Parser::PrintNode(std::shared_ptr<Node> object)
{
    ObjectNode* node = dynamic_cast<ObjectNode*>(object.get());

    if (node->id_.empty())
        std::cout << node->name_ << std::endl;
    else
        std::cout << node->name_ << ':' << node->id_ << std::endl;

    std::cout << '{' << std::endl;

    for (unsigned int i = 0; i < node->child_nodes_.size(); i++)
    {
        const std::shared_ptr<Node> child = node->child_nodes_[i];

        if (child->type_ == NodeType::kObjectNode)
            Parser::PrintNode(child);
        else
        {
            AttributeNode* node = dynamic_cast<AttributeNode*>(child.get());
            std::cout << node->name_ << '=' << node->value_ << std::endl;
        }
    }

    std::cout << '}' << std::endl;
}

bool Parser::GetTokenAdvance(Token& token)
{
    if (this->pos_ >= this->tokens_.size())
        return false;

    token = this->tokens_[this->pos_];

    this->pos_++;

    if (token.type_ == TokenType::kEOF)
        return false;

    return true;
}

inline Token Parser::GetLastToken(int offset)
{
    const int index = this->pos_ + offset - 2;

    if (index <= 0)
        return Token(TokenType::kUndefined);

    return this->tokens_[index];
}

inline Token Parser::GetCurrentToken(int offset)
{
    const int index = this->pos_ + offset - 1;

    if (index >= this->tokens_.size())
        return Token(TokenType::kUndefined);

    return this->tokens_[index];
}

inline Token Parser::GetNextToken(int offset)
{
    const int index = this->pos_ + offset;

    if (index >= this->tokens_.size())
        return Token(TokenType::kUndefined);

    return this->tokens_[index];
}

void Parser::ProcessTokens(std::shared_ptr<Node> parent_node)
{
    Token token(TokenType::kUndefined);
    while (this->GetTokenAdvance(token))
    {
        // Check for the end of an object
        if (token.type_ == TokenType::kCBracketClose)
        {
            if (parent_node->type_ == NodeType::kRootNode)
                // TODO: Error - Unexpected symbol '}'
                ;

            break;
        }

        if (this->CurrentNodeIsObject())
            this->CreateObjectNode(parent_node);
        else
            this->CreateAttributeNode(parent_node);
    }
}

void Parser::CreateObjectNode(std::shared_ptr<Node> parent_node)
{
    const size_t start_position = this->GetCurrentToken().position_.start_;

    const std::string name = this->GetCurrentToken().value_;
    std::string id;

    // Set position to bracket or colon
    this->pos_++;

    Token next_token    = this->GetNextToken();
    Token current_token = this->GetCurrentToken();

    // Check if the ID of the token is defined
    if (this->GetCurrentToken().type_ == TokenType::kColon)
    {
        id = this->GetNextToken().value_;

        // Skip the colon and id token
        this->pos_ += 2;
    }

    if (this->GetCurrentToken().type_ != TokenType::kCBracketOpen)
        // TODO: Error handling
        ;

    next_token = this->GetNextToken();
    current_token = this->GetCurrentToken();

    std::shared_ptr<Node> node = std::make_shared<ObjectNode>(name, id,
        Position(start_position, this->GetCurrentToken().position_.end_));

    this->ProcessTokens(node);

    parent_node->child_nodes_.push_back(node);
}

void Parser::CreateAttributeNode(std::shared_ptr<Node> parent_node)
{
    const size_t start_position = this->GetCurrentToken().position_.start_;

    const std::string name = this->GetCurrentToken().value_;
    std::string value;

    if (this->GetNextToken().type_ != TokenType::kEqual)
        // TOOD: Error - No equal symbol
        ;

    // Skip equal symbol
    this->pos_ += 2;

    Token token = this->GetCurrentToken();

    if (token.type_ == TokenType::kSBracketOpen)
        value = this->CreateArray();
    else if (token.type_ == TokenType::kBracketOpen)
        value = this->CreateVector();
    else
        value = token.value_;

    std::shared_ptr<AttributeNode> node = std::make_shared<AttributeNode>(
        name, value, token.type_,
        // We will use the function GetCurrenToken again, because the
        // CreateVector and CreateArray function may have changed the
        // current token.
        Position(start_position, this->GetCurrentToken().position_.end_));

    parent_node->child_nodes_.push_back(node);
}

bool Parser::CurrentNodeIsObject()
{
    if (this->GetCurrentToken().type_ == TokenType::kData &&
        (this->GetNextToken().type_ == TokenType::kColon ||
         this->GetNextToken().type_ == TokenType::kCBracketOpen))
    {
        return true;
    }

    return false;
}

std::string Parser::CreateArray()
{
    std::string value;
    Token token(TokenType::kUndefined);

    // The GetTokenAdvance function will skip the bracket
    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kSBracketClose)
        {
            break;
        }

        if (token.type_ == TokenType::kComma)
            value += ',';
        else
            value += token.value_;
    }

    return value;
}

std::string Parser::CreateVector()
{
    std::string value;
    Token token(TokenType::kUndefined);

    // The GetTokenAdvance function will skip the bracket
    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kBracketClose)
        {
            break;
        }

        if (token.type_ == TokenType::kComma)
            value += ',';
        else
            value += token.value_;
    }

    return value;
}

}  // namespace gui
