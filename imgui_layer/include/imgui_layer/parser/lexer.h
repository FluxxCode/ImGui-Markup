#ifndef IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_
#define IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_

#include "imgui_layer/parser/parser_result.h"

#include <fstream>
#include <string>

namespace gui
{

enum class LexerTokenType
{
    kUndefined,      // Undefined token that is returned when e.g. the
                     // LookAhead function gets called when there is no more
                     // token left.
    kColon,          // :
    kComma,          // ,
    kEqual,          // =
    kBracketOpen,    // (
    kBracketClose,   // )
    kCBracketOpen,   // {
    kCBracketClose,  // }
    kString,         // "<text>"
    kNumber,         // Int or float
    kData,           // Words containing alphabetical, numeric characters
                     // and '_'
    kEOF             // End of file
};

struct LexerToken
{
    LexerToken();
    LexerToken(const LexerTokenType type, const ParserPosition position);
    LexerToken(const LexerTokenType type, const ParserPosition position,
               const std::string data);

    LexerTokenType type;
    ParserPosition position;
    std::string data;
};

/* Exceptions */
struct LexerException
{
    LexerException(std::string message, LexerToken token, ParserResultType type)
        : message(message), token(token), type(type)
    { }

    const std::string message;
    const LexerToken token;
    const ParserResultType type;
};

struct FileNotFound : public LexerException
{
    FileNotFound(LexerToken token)
        : LexerException("File does not exists", token,
                         ParserResultType::kFileNotFound)
    { }
};

struct UnableToOpenFile : public LexerException
{
    UnableToOpenFile(LexerToken token)
        : LexerException("Unable to open file", token,
                         ParserResultType::kUnableToOpenFile)
    { }
};

struct InvalidSymbol : public LexerException
{
    InvalidSymbol(LexerToken token)
        : LexerException("Invalid symbol", token,
                         ParserResultType::kInvalidSymbol)
    { }
};

struct UnknownLexerInstruction : public LexerException
{
    UnknownLexerInstruction(LexerToken token)
        : LexerException("Unknown lexer instruction", token,
                         ParserResultType::kUnknownLexerInstruction)
    { }
};

struct WrongIncludeArgument : public LexerException
{
    WrongIncludeArgument(LexerToken token)
        : LexerException("Expecting string after include instruction", token,
                         ParserResultType::kIncludeFileDoesNotExists)
    { }
};

struct IncludePathDoesNotExists : public LexerException
{
    IncludePathDoesNotExists(LexerToken token)
        : LexerException("Include file does not exists", token,
                         ParserResultType::kIncludeFileDoesNotExists)
    { }
};

struct UnableToOpenIncludeFile : public LexerException
{
    UnableToOpenIncludeFile(LexerToken token)
        : LexerException("Unable to open include file", token,
                         ParserResultType::kUnableToOpenIncludeFile)
    { }
};

struct FileIncludesItself : public LexerException
{
    FileIncludesItself(LexerToken token)
        : LexerException("File includes itself", token,
                         ParserResultType::kFileIncludesItself)
    { }
};

struct UnexpectedEndOfString : public LexerException
{
    UnexpectedEndOfString(LexerToken token)
        : LexerException("Unexpected end of string", token,
                         ParserResultType::kUnexpectedEndOfString)
    { }
};

struct InvalidNumber : public LexerException
{
    InvalidNumber(LexerToken token)
        : LexerException("Invalid number", token,
                         ParserResultType::kInvalidNumber)
    { }
};


/**
 * Class to convert the contents of a file to tokens.
 * It is build to work together with the parser and not as a standalone class.
 */
class Lexer
{
public:
    /**
     * Resets the lexer and sets the mode to generate the tokens based
     * from the data of a file.
     *
     * @param path - Path to the file from where the tokens will be loaded.
     *               Absolute and relative paths are allowed.
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    void InitFile(const std::string path);

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
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    bool GetNextToken(LexerToken& dest);

    /**
     * Gets the next token in the data without incrementing the current position
     * and also stores it in the look ahead buffer.
     * The look ahead buffer is a cache which is used by the
     * GetNextToken function.
     *
     * @param offset - Offset from the current position.
     *                 Offset = 0 is the current token, while offset = 1 is
     *                 the next token.
     * @return The token at the current position plus the given offset.
     *         The token type will be set to kUndefined if the offset is
     *         out of range.
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    LexerToken LookAhead(const size_t offset = 1);

    /**
     * Resets the entire lexer and delete the data.
     */
    void Reset();

    static std::string TokenToString(LexerToken token);

private:
    struct File
    {
        explicit File(std::string path);

        /**
         * Path to the file
         */
        std::string path;

        /**
         * Main file handle
         */
        std::ifstream file;

        /**
         * Current virtual cursor position in the current line that is
         * being porcessed.
         */
        size_t position_in_line = 0;

        /**
         * Current line of the file that is processed.
         */
        std::string current_line;

        /**
         * Number of the current line.
         */
        size_t line_number = 0;
    };
    std::vector<File> file_stack_;

    /**
     * Buffer that stores tokens that were loaded by the LookAhead function.
     * The tokens in the buffer are used and removed by the GetNextToken
     * function if tokens exists. This should prevent the loss and mulitple
     * loading of tokens generated by the LookoAhead function.
     */
    std::vector<LexerToken> token_buffer_;

    LexerToken last_token_;

    /**
     * Opens a file and adds it to the file_stack.
     *
     * @param path - Path to the file that will be added
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
    */
    void OpenFile(const std::string path);

    /**
     * Closes every file handle on the file stack.
     */
    void CloseFiles();

    /**
     * Removes and closes the file handle of current file
     * that is on top of the file stack.
     */
    void RemoveCurrentFile();

    /**
     * Gets the next char at the current position and increments it.
     *
     * @param dest - Buffer that will recive the char.
     *               The buffer wount be changed if there arent any chars left.
     * @return true if there are still chars left to process
     * @return false if there isno more char left to process and the
     *         current char is at the end of the file. The buffer
     *         wount be changed if there is no token left to process.
     */
    bool GetNextChar(char& dest);

    /**
     * Gets the current character that is being processed, without
     * incrementing the current position.
     *
     * @param offset - Offset of the character in the line.
     *                 An offset of 0 is the current char. If the offset is
     *                 out of range of the current line, a char with the
     *                 value 0 will be returned.
     */
    char GetCurrentChar(size_t offset = 0) const;

    /**
     * Generates the next token and increments the current buffer position.
     * The function also opens new files (@include <file_path>) and also
     * closes files that are finished processing.
     */
    LexerToken GenerateToken();

    /**
     * Checks if the char at the current position is the start of a comment.
     */
    bool IsComment() const;

    /**
     * Assumes that the current char is the start of a comment.
     * The function will skip the chars until the comment end.
     */
    void SkipComment();

    /**
     * Assumes that the current char is the start of a string.
     * Every string starts with " and ends with ".
     * Comments and lexer instructions are ignored and
     * included inside the string.
     *
     * @return Created token with the string data
     */
    LexerToken CreateString();

    /**
     * Assumes that the current char is the start of a number.
     * Int and float numbers are supported.
     *
     * @return Created token with the number as a string
     */
    LexerToken CreateNumber();

    /**
     * Assumes that the current char is the start of some data.
     * Every data block can include:
     *   - Alphabetical characters
     *   - Numbers
     *   - Dots (.)
     *   - Underscores (_)
     * The data block will end after any character that is not listed above.
     * Data block examples:
     *   - Button
     *   - button_1.child_0.child_1.child_2
     *   - button_id
     *
     * @return Created token with the data as a string
     */
    LexerToken CreateData();

    /**
     * Assumes that the current char is the start of a lexer instruction.
     * Lexer instructions start with a '@'.
     * The following lexer instructions are implemented:
     *   - <@>include "<file>"
     *
     * @return LexerToken after the instruction is executed.
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    LexerToken ProcessLexerInstruction();

    /**
     * Assumes that the current char is the start of the first argument
     * of the include instruction.
     * The include instruction will open a new file and add it to the
     * file stack. It takes one argument of type string, which is the path
     * to the file that will be opened. The path has to be relative to the
     * file from where the instruction is executed.
     *
     * @return The first token of the new file.
     * @throws The function can throw lexer and std exceptions.
     *         The parser will only catch the lexer exceptions.
     *         Every other exceptions is not catched by the parser!
     */
    LexerToken ProcessIncludeInstruction();

    /**
     * Used to construct LexerTokens with a different amount of arguments.
     * The functions will also set the file stack and the current line
     * of the token.
     */
    LexerToken ConstructToken(LexerTokenType type) const;
    LexerToken ConstructToken(LexerTokenType type, std::string data) const;
    LexerToken ConstructToken(LexerTokenType type, std::string data,
                              size_t start, size_t end) const;
    std::vector<std::string> ConvertFileStack() const;

    /**
     * Returns the current line position.
     * 0 will be returned if there is no file on the file stack.
     */
    size_t GetCurrentPosition() const;

    /**
     * Returns the path of the current directory from where the current file
     * is processed.
     * The function will return an empty string if there are
     * currently no files on the file stack.
     */
    std::string GetCurrentDirectory() const;
};

}  // namespace gui

#endif  // IMGUI_LAYER_INCLUDE_IMGUI_LAYER_PARSER_LEXER_H_
