#ifndef IMGUI_LAYER_SRC_PARSER_PARSER_ERROR_H_
#define IMGUI_LAYER_SRC_PARSER_PARSER_ERROR_H_

namespace gui
{

struct Position
{
    Position();
    Position(const size_t start);
    Position(const size_t start, const size_t end);

    size_t start_;
    size_t end_;
};

enum class ParserErrorType
{
    kUndefined,
    kUnableToOpenFile,
    kFileDoesNotExists,
    kUnexpectedSymbol,
    kInvalidAttributeName,
    kInvalidObjectID,
    kConversionError
};

class ParserError
{
public:
    // Constructors
    ParserError();

    ParserError(
        const ParserErrorType type,
        const std::string message);

    ParserError(
        const ParserErrorType type,
        const Position position,
        const std::string message,
        const std::string& data);

    // Variables
    ParserErrorType type_;
    Position position_;
    std::string message_;

    // Functions
    /**
     * Convert the parser error to a string. The format will be:
     *
     * Error: "<message>"
     * Line: 25
     * title "238" = "This is a title"
     *       ^^^^^
     *
     * @return the error as a string.
    */
    std::string ToString() const;

private:
    // Variables
    size_t line_number_ = 0;
    size_t pos_in_line_ = 0;
    std::string line_;

    // Functions
    bool GetErrorPositionInLine(const std::string& data);
};

}  // namespcae gui

#endif  // IMGUI_LAYER_SRC_PARSER_PARSER_ERROR_H_
