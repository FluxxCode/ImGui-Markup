#ifndef IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_
#define IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_

namespace gui
{

enum class ParserResultType
{
    kSuccess,
    kFileNotFound,
    kUnableToOpenFile
};

class ParserResult
{
public:
    ParserResult();
    ParserResult(ParserResultType type);

    ParserResultType type_;

    bool operator==(const ParserResultType& right);
};

}  // namespace gui

#endif IMGUI_LAYER_INCLUDE_PARSER_PARSER_RESULT_H_
