#ifndef IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_
#define IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_

#include <string>

namespace gui
{

enum class ParserResultType
{
    kSuccess,
    kFileNotFound,
    kUnableToOpenFile,
    kInvalidSymbol,
    kUnknownLexerInstruction,
    kWrongIncludeArgument,
    kIncludeFileDoesNotExists,
    kUnableToOpenIncludeFile,
    kFileIncludesItself,
    kUnexpectedEndOfString,
    kInvalidNumber
};

class ParserResult
{
public:
    ParserResult();
    ParserResult(ParserResultType type);

    ParserResultType type_;

    std::string ToString() const;

    operator bool() const;
private:
    static std::string ResultTypeToString(const ParserResultType type);
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_
