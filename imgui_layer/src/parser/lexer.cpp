#include "ilpch.h"
#include "lexer.h"

namespace gui
{

Lexer::Lexer(const std::string text)
    : text_(text)
{ }

std::vector<Token> Lexer::GetTokens()
{
    std::vector<Token> tokens;
    Token last_token = Token(TokenType::kUndefined);

    char c;
    while (this->GetCharAdvance(c))
    {
        // Skip white space
        if (std::isspace(c))
            continue;

        typedef TokenType Type;
        typedef Position  Pos;

        // Check for comments
        if (this->IsComment(c))
        {
            this->SkipComment();
            continue;
        }
        else if (c == ':')
            tokens.push_back(Token(Type::kColon,         Pos(this->pos_ - 1)));
        else if (c == ',')
            tokens.push_back(Token(Type::kComma,         Pos(this->pos_ - 1)));
        else if (c == '=')
            tokens.push_back(Token(Type::kEqual,         Pos(this->pos_ - 1)));
        else if (c == '@')
            tokens.push_back(Token(Type::kAt,            Pos(this->pos_ - 1)));
        else if (c == '(')
            tokens.push_back(Token(Type::kBracketOpen,   Pos(this->pos_ - 1)));
        else if (c == ')')
            tokens.push_back(Token(Type::kBracketClose,  Pos(this->pos_ - 1)));
        else if (c == '[')
            tokens.push_back(Token(Type::kSBracketOpen,  Pos(this->pos_ - 1)));
        else if (c == ']')
            tokens.push_back(Token(Type::kSBracketClose, Pos(this->pos_ - 1)));
        else if (c == '{')
            tokens.push_back(Token(Type::kCBracketOpen,  Pos(this->pos_ - 1)));
        else if (c == '}')
            tokens.push_back(Token(Type::kCBracketClose, Pos(this->pos_ - 1)));
        else if (c == '"')
            tokens.push_back(this->CreateString());
        else if (std::isdigit(c))
            tokens.push_back(this->CreateNumber());
        else
            tokens.push_back(this->CreateData());

        last_token = tokens[tokens.size() - 1];
    }

    tokens.emplace_back(Token(TokenType::kEOF));

    return tokens;
}

std::string Lexer::TokenToString(Token token)
{
    std::string message = "[";

    switch (token.type_)
    {
    case TokenType::kColon:
        message += "COL";
        break;

    case TokenType::kComma:
        message += "COM";
        break;

    case TokenType::kEqual:
        message += "EQU";
        break;

    case TokenType::kAt:
        message += "AT";
        break;

    case TokenType::kBracketOpen:
        message += "BO";
        break;

    case TokenType::kBracketClose:
        message += "BC";
        break;

    case TokenType::kSBracketOpen:
        message += "SBO";
        break;

    case TokenType::kSBracketClose:
        message += "SBC";
        break;

    case TokenType::kCBracketOpen:
        message += "CBO";
        break;

    case TokenType::kCBracketClose:
        message += "CBC";
        break;

    case TokenType::kString:
        message += "STR=" + token.value_;
        break;

    case TokenType::kInt:
        message += "INT=" + token.value_;
        break;

    case TokenType::kFloat:
        message += "FLT=" + token.value_;
        break;

    case TokenType::kData:
        message += "DAT=" + token.value_;
        break;

    case TokenType::kEOF:
        message += "EOF";
        break;

    default:
        message += "UND=" + token.value_;
        break;
    }

    return message + ']';
}

bool Lexer::GetCharAdvance(char& c)
{
    if (this->pos_ >= this->text_.size())
        return false;

    c = this->text_[this->pos_];

    this->pos_++;

    return true;
}

inline char Lexer::GetLastChar()
{
    if (this->pos_ - 2 <= 0)
        return 0;

    return this->text_[this->pos_ - 2];
}

inline char Lexer::GetCurrentChar()
{
    if (this->pos_ - 1 >= this->text_.size())
        return 0;

    return this->text_[this->pos_ - 1];
}

inline char Lexer::GetNextChar()
{
    if (this->pos_ >= this->text_.size())
        return 0;

    return this->text_[this->pos_];
}

bool Lexer::IsComment(const char c)
{
    if (c == '#' ||
       (c == '/' && this->GetNextChar() == '/') ||
       (c == '/' && this->GetNextChar() == '*'))
    {
        return true;
    }

    return false;
}

void Lexer::SkipComment()
{
    bool multi_line = false;

    char c = this->GetNextChar();

    if (c == '*')
        multi_line = true;

    while (this->GetCharAdvance(c))
    {
        if (!multi_line && c == '\n')
            break;
        else if (multi_line && c == '*' && this->GetNextChar() == '/')
        {
            this->pos_++;
            break;
        }
    }
}

Token Lexer::CreateString()
{
    std::string value;

    size_t start_pos = this->pos_ - 1;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (c == '"' && this->GetLastChar() != '\\')
            break;

        if (c == '\\' && this->GetNextChar() == '"')
            continue;

        value += c;
    }

    return Token(TokenType::kString, value,
        Position(start_pos, this->pos_ - 1));
}

Token Lexer::CreateNumber()
{
    std::string value;
    value += this->GetCurrentChar();

    size_t dot_count = 0;
    size_t start_pos = this->pos_ - 1;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c) ||
            c == ',' ||
            c == ')' ||
            c == ']' ||
            c == '}')
        {
            this->pos_--;
            break;
        }

        if (this->IsComment(c))
        {
            this->SkipComment();
            continue;
        }

        if (c == '.')
            dot_count++;

        if (!std::isdigit(c))
            // TODO: ERROR
            ;

        value += c;
    }

    if (dot_count > 1)
        // TODO: ERROR
        ;

    if (dot_count == 1)
    {
        return Token(TokenType::kFloat, value,
            Position(start_pos, this->pos_ - 1));
    }

    return Token(TokenType::kInt, value, Position(start_pos, this->pos_ - 1));
}

Token Lexer::CreateData()
{
    std::string value;
    value += this->GetCurrentChar();

    size_t start_pos = this->pos_ - 1;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c) ||
            c == ',' ||
            c == ')' ||
            c == ']' ||
            c == '}')
        {
            this->pos_--;
            break;
        }

        if (this->IsComment(c))
        {
            this->SkipComment();
            break;
        }

        value += c;
    }

    return Token(TokenType::kData, value, Position(start_pos, this->pos_ - 1));
}

}  // namespace gui
