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

    char c;
    while (this->GetCharAdvance(c))
    {
        // Skip white space
        if (std::isspace(c))
            continue;

        // Check for comments
        if (this->IsComment(c))
            this->SkipComment();
        else if (c == '.')
            tokens.emplace_back(Token(TokenType::kDot));
        else if (c == ':')
            tokens.emplace_back(Token(TokenType::kColon));
        else if (c == '=')
            tokens.emplace_back(Token(TokenType::kEqual));
        else if (c == '@')
            tokens.emplace_back(Token(TokenType::kAt));
        else if (c == '{')
            tokens.emplace_back(Token(TokenType::kOpen));
        else if (c == '}')
            tokens.emplace_back(Token(TokenType::kClose));
        else if (c == '"')
            tokens.push_back(this->CreateString());
        else if (c == '[')
            tokens.push_back(this->CreateArray());
        else if (c == '(')
            tokens.push_back(this->CreateVector());
        else if (std::isdigit(c))
            tokens.push_back(this->CreateNumber());
        else
            tokens.push_back(this->CreateData());
    }

    return tokens;
}

std::string Lexer::TokenToString(Token token)
{
    std::string message = "[";

    switch (token.type_)
    {
    case TokenType::kDot:
        message += "DOT";
        break;

    case TokenType::kColon:
        message += "COL";
        break;

    case TokenType::kEqual:
        message += "EQU";
        break;

    case TokenType::kAt:
        message += "AT";
        break;

    case TokenType::kOpen:
        message += "OPEN";
        break;

    case TokenType::kClose:
        message += "CLOSE";
        break;

    case TokenType::kString:
        message += "STR=" + token.value_;
        break;

    case TokenType::kArray:
        message += "ARR=" + token.value_;
        break;

    case TokenType::kVector:
        message += "VEC=" + token.value_;
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

    char c;
    while (this->GetCharAdvance(c))
    {
        if (c == '"' && this->GetLastChar() != '\\')
            break;

        if (c == '\\' && this->GetNextChar() == '"')
            continue;

        value += c;
    }

    return Token(TokenType::kString, value);
}

Token Lexer::CreateArray()
{
    std::string value;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c))
            continue;

        if (this->IsComment(c))
        {
            this->SkipComment();
            continue;
        }

        if (c == ']')
            break;

        value += c;
    }

    return Token(TokenType::kArray, value);
}

Token Lexer::CreateVector()
{
    std::string value;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c))
            continue;

        if (this->IsComment(c))
        {
            this->SkipComment();
            continue;
        }

        if (c == ')')
            break;

        value += c;
    }

    return Token(TokenType::kVector, value);
}

Token Lexer::CreateNumber()
{
    std::string value;
    value += this->GetCurrentChar();

    size_t dot_count = 0;

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c))
            break;

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
        return Token(TokenType::kFloat, value);

    return Token(TokenType::kInt, value);
}

Token Lexer::CreateData()
{
    std::string value;
    value += this->GetCurrentChar();

    char c;
    while (this->GetCharAdvance(c))
    {
        if (std::isspace(c))
            break;

        if (this->IsComment(c))
        {
            this->SkipComment();
            continue;
        }

        value += c;
    }

    return Token(TokenType::kData, value);
}

}  // namespace gui
