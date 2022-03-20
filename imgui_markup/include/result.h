#ifndef IMGUI_LAYER_INCLUDE_RESULT_H_
#define IMGUI_LAYER_INCLUDE_RESULT_H_

#include <string>

namespace igm
{

enum class ResultType
{
    kSuccess,
    kParserError,
    kInvalidContextID,
    kInvalidItemID
};

struct Result
{
    Result()
        : type(ResultType::kSuccess), message("Success")
    { }

    Result(ResultType type, std::string message)
        : type(type), message(message)
    { }

    ResultType type;
    std::string message;
};

}  // namespace igm

#endif  // IMGUI_LAYER_INCLUDE_RESULT_H_
