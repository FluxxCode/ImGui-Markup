#include "impch.h"
#include "parser/parser.h"

#include <iostream>

namespace imgui_markup::internal::parser
{

/* Parser */
ParserResult Parser::ParseFile(const std::string file, FileContext& dest)
{
    this->Reset();

    try
    {
        FileContext file_context;

        this->lexer_.InitFile(file);

        std::shared_ptr<ParserNode> root_node = std::make_shared<ParserNode>(
            ParserNodeType::kRootNode, ParserPosition({file}, "", 0, 0, 0));

        this->ProcessTokens(root_node);

        this->interpreter_.ConvertNodeTree(root_node, dest);
    }
    catch(const LexerException& e)
    {
        return ParserResult(e.type, e.message, e.token.position);
    }
    catch (const ParserException& e)
    {
        return ParserResult(e.type, e.message, e.token.position);
    }
    catch (const InterpreterException& e)
    {
        return ParserResult(e.type, e.message, e.node.position);
    }

    return ParserResult(ParserResultType::kSuccess);
}

void Parser::Reset()
{
    this->lexer_.Reset();
    this->interpreter_.Reset();
}

void Parser::ProcessTokens(std::shared_ptr<ParserNode> parent_node)
{
    if (!parent_node)
        return;

    LexerToken token;
    while (this->lexer_.GetNextToken(token))
    {
        if (this->TokenIsBlockEnd(*parent_node))
            return;

        if (this->TokenIsItemNode())
            this->CreateItemNode(*parent_node);
        else if (TokenIsAttributeAssignNode())
            this->CreateAttributeAssignNode(*parent_node);
        else
            throw UndefinedTokenSequence(token);
    }
}

bool Parser::TokenIsBlockEnd(const ParserNode& current_node)
{
    LexerToken token = this->lexer_.LookAhead(0);
    if (token.type == LexerTokenType::kCBracketClose)
    {
        if (current_node.type == ParserNodeType::kRootNode)
            throw UnexpectedBlockEnd(token);

        return true;
    }

    return false;
}

/* Item node */
bool Parser::TokenIsItemNode()
{
    const LexerToken current_token = this->lexer_.LookAhead(0);
    const LexerToken next_token    = this->lexer_.LookAhead(1);

    if (current_token.type != LexerTokenType::kID)
        return false;

    if (next_token.type == LexerTokenType::kCBracketOpen ||
        next_token.type == LexerTokenType::kColon)
    {
        return true;
    }

    return false;
}

void Parser::CreateItemNode(ParserNode& parent_node)
{
    LexerToken token = this->lexer_.LookAhead(0);
    ParserPosition item_position = token.position;

    const std::string type = token.data;
    std::string id = "";

    size_t end_position = this->lexer_.LookAhead(0).position.end;

    if (!this->lexer_.GetNextToken(token))
        throw UnexpectedEndOfFile(this->lexer_.LookAhead(0));


    // Check if the ID is set
    if (token.type == LexerTokenType::kColon)
    {
        if (!this->lexer_.GetNextToken(token))
            throw UnexpectedEndOfFile(this->lexer_.LookAhead(0));

        if (token.type != LexerTokenType::kID)
            throw ItemIDWrongValueType(token);

        id = token.data;
        end_position = token.position.end;

        end_position = this->lexer_.LookAhead(0).position.end;

        // Move one token, where we expect the start of the item block
        if (!this->lexer_.GetNextToken(token))
            throw UnexpectedEndOfFile(this->lexer_.LookAhead(0));
    }

    if (token.type != LexerTokenType::kCBracketOpen)
        throw ExpectedStartOfBlock(token);

    item_position.end = end_position;

    std::shared_ptr<ParserNode> node =
        std::make_shared<ParserItemNode>(type, id, item_position);

    if (!node)
        throw UnableToCreateItemNode(token);

    this->ProcessTokens(node);

    parent_node.child_nodes.push_back(node);
}

/* AttributeBase assign node */
bool Parser::TokenIsAttributeAssignNode()
{
    const LexerToken current_token = this->lexer_.LookAhead(0);
    const LexerToken next_token    = this->lexer_.LookAhead(1);

    if (current_token.type == LexerTokenType::kID &&
        next_token.type    == LexerTokenType::kEqual)
    {
        return true;
    }

    return false;
}

void Parser::CreateAttributeAssignNode(ParserNode& parent_node)
{
    const std::string name = this->lexer_.LookAhead(0).data;

    ParserPosition position = this->lexer_.LookAhead(0).position;

    LexerToken token;
    if (!this->lexer_.GetNextToken(token))
        throw UnexpectedEndOfFile(this->lexer_.LookAhead(0));

    if (token.type != LexerTokenType::kEqual)
        throw ExpectedEqualSymbol(token);

    // Skip equal symbol
    if (!this->lexer_.GetNextToken(token))
        throw UnexpectedEndOfFile(this->lexer_.LookAhead(0));

    std::shared_ptr<ParserNode> value_node;

    if (this->TokenIsStringNode())
        value_node = this->CreateStringNode();
    else if (this->TokenIsIntNode())
        value_node = this->CreateIntNode();
    else if (this->TokenIsFloatNode())
        value_node = this->CreateFloatNode();
    else if (this->TokenIsBoolNode())
        value_node = this->CreateBoolNode();
    else if (this->TokenIsVectorNode())
        value_node = this->CreateVectorNode();
    else if(this->TokenIsAttributeReferenceNode())
        value_node = this->CreateAttributeReferenceNode();
    else
        throw ValueNodeWrongType(token);

    position.end = value_node->position.end;

    std::shared_ptr<ParserNode> node =
        std::make_shared<ParserAttributeAssignNode>(name, value_node, position);

    if (!node)
        throw UnableToCreateAttributeAssignNode(token);

    parent_node.child_nodes.push_back(node);
}

/* String node */
bool Parser::TokenIsStringNode()
{
    return this->lexer_.LookAhead(0).type == LexerTokenType::kString
                ? true : false;
}

std::shared_ptr<ParserStringNode> Parser::CreateStringNode()
{
    const LexerToken token = this->lexer_.LookAhead(0);
    if (token.type != LexerTokenType::kString)
        throw ValueNodeWrongType(token);

    std::shared_ptr<ParserStringNode> node =
        std::make_shared<ParserStringNode>(token.data, token.position);

    if (!node)
        throw UnableToCreateStringNode(token);

    return node;
}

/* Number node */
bool Parser::TokenIsIntNode()
{
    return this->lexer_.LookAhead(0).type == LexerTokenType::kInt
                ? true : false;
}

std::shared_ptr<ParserIntNode> Parser::CreateIntNode()
{
    const LexerToken token = this->lexer_.LookAhead(0);
    if (token.type != LexerTokenType::kInt)
        throw ValueNodeWrongType(token);

    std::shared_ptr<ParserIntNode> node =
        std::make_shared<ParserIntNode>(token.data, token.position);

    if (!node)
        throw UnableToCreateNumberNode(token);

    return node;
}

/* Float node */
bool Parser::TokenIsFloatNode()
{
    return this->lexer_.LookAhead(0).type == LexerTokenType::kFloat
                ? true : false;
}

std::shared_ptr<ParserFloatNode> Parser::CreateFloatNode()
{
    const LexerToken token = this->lexer_.LookAhead(0);
    if (token.type != LexerTokenType::kFloat)
        throw ValueNodeWrongType(token);

    std::shared_ptr<ParserFloatNode> node =
        std::make_shared<ParserFloatNode>(token.data, token.position);

    if (!node)
        throw UnableToCreateNumberNode(token);

    return node;
}

/* Bool node */
bool Parser::TokenIsBoolNode()
{
    return this->lexer_.LookAhead(0).type == LexerTokenType::kBool
                ? true : false;
}

std::shared_ptr<ParserBoolNode> Parser::CreateBoolNode()
{
    const LexerToken token = this->lexer_.LookAhead(0);
    if (token.type != LexerTokenType::kBool)
        throw ValueNodeWrongType(token);

    std::shared_ptr<ParserBoolNode> node =
        std::make_shared<ParserBoolNode>(token.data, token.position);

    if (!node)
        throw UnableToCreateBoolNode(token);

    return node;
}

/* Vector node */
bool Parser::TokenIsVectorNode()
{
    return this->lexer_.LookAhead(0).type == LexerTokenType::kBracketOpen
                ? true : false;
}

std::shared_ptr<ParserVectorNode> Parser::CreateVectorNode()
{
    LexerToken token = this->lexer_.LookAhead(0);

    if (token.type != LexerTokenType::kBracketOpen)
        throw ValueNodeWrongType(token);

    const size_t start_position = token.position.start;

    std::shared_ptr<ParserVectorNode> node =
        std::make_shared<ParserVectorNode>(token.position);

    if (!node)
        throw UnableToCreateVectorNode(token);

    while (token.type != LexerTokenType::kBracketClose)
    {
        if (!this->lexer_.GetNextToken(token))
            throw UnexpectedEndOfFile(token);
        if (token.type == LexerTokenType::kComma)
        {
            if (this->lexer_.LookAhead(1).type == LexerTokenType::kComma ||
                this->lexer_.LookAhead(1).type == LexerTokenType::kBracketClose)
            {
                throw MissingVectorValue(token);
            }
            continue;
        }
        if (token.type == LexerTokenType::kBracketClose)
            break;

        std::shared_ptr<ParserNode> value_node;

        if (this->TokenIsStringNode())
            value_node = this->CreateStringNode();
        else if (this->TokenIsIntNode())
            value_node = this->CreateIntNode();
        else if (this->TokenIsFloatNode())
            value_node = this->CreateFloatNode();
        else if(this->TokenIsAttributeReferenceNode())
            value_node = this->CreateAttributeReferenceNode();
        else
            throw ValueNodeWrongType(token);

        node->child_nodes.push_back(value_node);
    }

    ParserPosition position = token.position;
    position.start = start_position;
    node->position = position;

    return node;
}

/* AttributeBase access node */
bool Parser::TokenIsAttributeReferenceNode()
{
    const LexerToken current_token = this->lexer_.LookAhead(0);

    if (current_token.type == LexerTokenType::kReference)
        return true;

    return false;
}

std::shared_ptr<ParserAttributeReferenceNode>
    Parser::CreateAttributeReferenceNode()
{
    const LexerToken token = this->lexer_.LookAhead(0);
    if (token.type != LexerTokenType::kReference)
        throw ValueNodeWrongType(token);

    std::shared_ptr<ParserAttributeReferenceNode> node =
        std::make_shared<ParserAttributeReferenceNode>(token.data, token.position);

    if (!node)
        throw UnableToCreateAttributeAccessNode(token);

    return node;
}

}  // namespace imgui_markup::internal::parser
