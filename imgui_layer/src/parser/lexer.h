#ifndef IMGUI_LAYER_SRC_PARSER_LEXER_H_
#define IMGUI_LAYER_SRC_PARSER_LEXER_H_

#include <vector>
#include <string>

namespace gui
{

enum class TokenType : unsigned char
{
    kUndefined,      //  Undefined token, not created by lexer
    kColon,          //  :
    kComma,          //  ,
    kEqual,          //  =
    kAt,             //  @
    kBracketOpen,    //  (
    kBracketClose,   //  )
    kSBracketOpen,   //  [
    kSBracketClose,  //  ]
    kCBracketOpen,   //  {
    kCBracketClose,  //  }
    kString,         //  "<data>"
    kInt,            //  1234
    kFloat,          //  1234.1234
    kData,           //  <data>  - Without space
    kEOF             //  End of file
};

struct Token
{
    Token(const TokenType type, const std::string value = "")
        : type_(type), value_(value)
    { }

    TokenType type_;
    std::string value_;
};

class Lexer
{
public:
    // Constructor
    Lexer(const std::string text);

    // Functions
    std::vector<Token> GetTokens();

    std::string TokenToString(Token token);

private:
    // Variables
    const std::string text_;
    int pos_ = 0;

    // Functions
    bool GetCharAdvance(char& c);
    inline char GetLastChar();
    inline char GetCurrentChar();
    inline char GetNextChar();

    bool IsComment(const char c);
    void SkipComment();

    Token CreateString();
    Token CreateNumber();
    Token CreateData();
};

}  // namespace gui

#endif  // IMGUI_LAYER_SRC_PARSER_LEXER_H_
