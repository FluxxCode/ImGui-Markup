#ifndef IMGUI_LAYER_SRC_PARSER_LEXER_H_
#define IMGUI_LAYER_SRC_PARSER_LEXER_H_

#include <vector>
#include <string>

namespace gui
{

enum class TokenType : unsigned char
{
    kDot,     //  .
    kColon,   //  :
    kEqual,   //  =
    kAt,      //  @
    kOpen,    //  {
    kClose,   //  }
    kString,  // "<data>"
    kArray,   // [<data>]
    kVector,  // (<data>)
    kInt,     // 1234
    kFloat,   // 1234.1234
    kData     // <data>
};

struct Token
{
    Token(const TokenType type, const std::string value = "")
        : type_(type), value_(value)
    { }

    const TokenType type_;
    const std::string value_;
};

class IMGUI_LAYER_API Lexer
{
public:
    // Constructor
    Lexer(const std::string text);

    // Functions
    std::vector<Token> GetTokens();

private:
    // Variables
    const std::string text_;
    size_t pos_ = 0;

    // Functions
    bool GetCharAdvance(char& c);
    inline char GetLastChar();
    inline char GetCurrentChar();
    inline char GetNextChar();

    bool IsComment(const char c);
    void SkipComment();

    Token CreateString();
    Token CreateArray();
    Token CreateVector();
    Token CreateNumber();
    Token CreateData();


    std::string TokenToString(Token token);
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_LEXER_H_
