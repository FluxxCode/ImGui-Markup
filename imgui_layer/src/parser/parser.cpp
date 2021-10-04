#include "ilpch.h"
#include "parser/parser.h"

namespace gui
{

/*****************************************************************************/

Node::Node(const NodeType type)
    : type_(type)
{ }

Node::~Node()
{ }

std::shared_ptr<Node> Node::operator[](unsigned int i) const
{
    return this->child_nodes_[i];
}

ObjectNode::ObjectNode(const std::string obj_name, const std::string id)
    : Node(NodeType::kObjectNode), name_(obj_name), id_(id)
{ }

AttributeNode::AttributeNode(
    const std::string name,
    const std::string value,
    const TokenType value_type)
    : Node(NodeType::kAttributeNode),
      name_(name), value_(value), value_type_(value_type)
{ }

/*****************************************************************************/

Parser::Parser(const std::vector<Token> tokens)
    : tokens_(tokens)
{ }

std::vector<std::shared_ptr<Node>> Parser::Parse()
{
    std::vector<std::shared_ptr<Node>> nodes;

    Token token(TokenType::kUndefined);
    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kCBracketOpen ||
            token.type_ == TokenType::kCBracketClose)
        {
            continue;
        }

        if (this->IsObject())
            nodes.push_back(this->CreateObject());
        else
            nodes.push_back(this->CreateAttribute());
    }

    return nodes;
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

bool Parser::IsObject()
{
    const Token token = this->GetCurrentToken();

    if (token.type_ != TokenType::kData)
        return false;

    if (this->GetLastToken().type_ == TokenType::kColon)
        return false;

    if (this->GetNextToken().type_  == TokenType::kColon &&
        this->GetNextToken(1).type_ == TokenType::kData)
    {
        return true;
    }

    if (this->GetNextToken().type_ == TokenType::kCBracketOpen)
        return true;

    return false;
}

std::shared_ptr<Node> Parser::CreateObject()
{
    std::shared_ptr<Node> node;
    const std::string name = this->GetCurrentToken().value_;

    if (this->GetNextToken().type_ == TokenType::kColon)
    {
        node = std::make_shared<ObjectNode>(name, this->GetNextToken(1).value_);
        this->pos_ += 2;
    }
    else
        node = std::make_shared<ObjectNode>(name);

    this->pos_++;

    Token token(TokenType::kUndefined);
    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kCBracketClose)
            break;

        if (this->IsObject())
            this->CreateObject(node);
        else
            this->CreateAttribute(node);
    }

    return node;
}

void Parser::CreateObject(std::shared_ptr<Node> node_in)
{
    std::shared_ptr<Node> node;
    const std::string name = this->GetCurrentToken().value_;

    if (this->GetNextToken().type_ == TokenType::kColon)
    {
        node = std::make_shared<ObjectNode>(name, this->GetNextToken(1).value_);
        this->pos_ += 2;
    }
    else
        node = std::make_shared<ObjectNode>(name);

    this->pos_++;

    Token token(TokenType::kUndefined);
    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kCBracketClose)
            break;

        if (this->IsObject())
            this->CreateObject(node);
        else
            this->CreateAttribute(node);
    }

    node_in->child_nodes_.push_back(node);
}

std::shared_ptr<Node> Parser::CreateAttribute()
{
    if (this->GetNextToken().type_ != TokenType::kEqual)
        // TODO: ERROR - Invalid Syntax
        ;

    const std::string name = this->GetCurrentToken().value_;
    std::string value;

    this->pos_++;

    if (this->GetNextToken().type_ == TokenType::kBracketOpen)
        value = this->CreateVector();
    else if (this->GetNextToken().type_ == TokenType::kSBracketOpen)
        value = this->CreateArray();
    else
        value = this->GetNextToken().value_;

    this->pos_++;

    return std::make_shared<AttributeNode>(
        name, value, this->GetCurrentToken().type_);
}

void Parser::CreateAttribute(std::shared_ptr<Node> node)
{
    if (this->GetNextToken().type_ != TokenType::kEqual)
        // TODO: ERROR - Invalid Syntax
        ;

    const std::string name = this->GetCurrentToken().value_;
    std::string value;

    this->pos_++;

    if (this->GetNextToken().type_ == TokenType::kBracketOpen)
        value = this->CreateVector();
    else if (this->GetNextToken().type_ == TokenType::kSBracketOpen)
        value = this->CreateArray();
    else
        value = this->GetNextToken().value_;

    this->pos_++;

    return node->child_nodes_.push_back(std::make_shared<AttributeNode>(
        name, value, this->GetCurrentToken().type_));
}

std::string Parser::CreateArray()
{
    std::string value;
    Token token(TokenType::kUndefined);

    // Skip bracket
    this->pos_++;

    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kSBracketClose)
        {
            this->pos_--;
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

    // Skip bracket
    this->pos_++;

    while (this->GetTokenAdvance(token))
    {
        if (token.type_ == TokenType::kBracketClose)
        {
            this->pos_--;
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
