#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_

#include "imgui_layer/parser/parser.h"

namespace gui
{

enum class LexerTokenType
{
    kUndefined,      // Undefined token that is returned when e.g. the
                     // LookAhead function gets called when there is no more
                     // token left.
    kDot,            // .
    kColon,          // :
    kComma,          // ,
    kEqual,          // =
    kAt,             // @
    kBracketOpen,    // (
    kBracketClose,   // )
    kSBracketOpen,   // [
    kSBracketClose,  // ]
    kCBracketOpen,   // {
    kCBracketClose,  // }
    kString,         // "<text>"
    kInt,            // 1234
    kFloat,          // 1234.1234
    kData,           // Words containing alphabetical, numeric characters
                     // and '_'
    kEOF             // End of file
};

struct LexerToken
{
    LexerToken(const LexerTokenType type);
    LexerToken(const LexerTokenType type, const std::string data);

    LexerTokenType type;
    std::string data;
};

class Lexer
{
public:
    /**
     * Resets the lexer and sets the mode to generate the tokens based
     * from the data of a file.
     *
     * @param path - Path to the file from where the tokens will be loaded.
     *               Absolute and relative paths are allowed.
     * @return Result of the operation as a ParserResult. The ParesrErrorType
     *         will be set to one of the following types:
     *              - kFileNotFound
     *              - kUnableToOpenFile
     */
    ParserResult InitFile(const std::string path);

    /**
     * Gets the next token in the data and increments
     * the current position by one. Keep in mind that the next token is
     * the token that is at the current position of the data.
     * This is because the current position gets incremented after the token
     * is processed. So the current position is always one ahead of the current
     * token.
     *
     * @param dest - Buffer receiving the token
     * @return true  If there are still tokens to process
     * @return false If there is no more token to process.
     */
    bool GetNextToken(LexerToken& dest);

    /**
     * Gets the next token in the data without incrementing the current position
     * in the data and also stores it in the look ahead buffer.
     * The look ahead buffer is a cache which is used by the
     * GetNextToken function.
     *
     * @param offset - Offset from the current position. Keep in mind that the
     *                 current position is always one ahead of the current
     *                 token position. So offset = 0 is the next token that
     *                 will be processed, while offset = -1 is the current
     *                 token (last token that was processed)
     * @return The token at the current position plus the given offset.
     *         The token type will be set to kUndefined if the offset is
     *         out of range.
     */
    LexerToken LookAhead(const int offset = 0);

    /**
     * Resets the entire lexer and delete the data.
     */
    void Reset();

private:
    struct File
    {
        std::ifstream file;
        size_t position = 0;
    };
    std::vector<File> file_stack_;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_
