#include "ilpch.h"
#include "imgui_layer/parser/lexer.h"

namespace gui
{

/* Lexer Token */
LexerToken::LexerToken(const LexerTokenType type)
    : type(type)
{ }

LexerToken::LexerToken(const LexerTokenType type, const std::string data)
    : type(type), data(data)
{ }

/* Lexer */
ParserResult Lexer::InitFile(const std::string path)
{
    this->Reset();

    if (!std::filesystem::exists(path))
        return ParserResult(ParserResultType::kFileNotFound);
}

bool Lexer::GetNextToken(LexerToken& dest)
{
    // TOOD: Implement
    return false;
}

LexerToken Lexer::LookAhead(const int offset)
{
    // TODO: Implement
    return LexerToken(LexerTokenType::kUndefined);
}

void Lexer::Reset()
{
    this->file_stack_.clear();
}

}  // namespace gui
