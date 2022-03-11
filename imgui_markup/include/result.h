#ifndef IMGUI_LAYER_INCLUDE_RESULT_H_
#define IMGUI_LAYER_INCLUDE_RESULT_H_

#include <string>

namespace imgui_markup
{

enum class ResultType
{
    kSucess,
    kParserError,
    kInvalidContextID,
    kInvalidItemID
};

struct Result
{
    Result()
        : type(ResultType::kSucess), message("Success")
    { }

    Result(ResultType type, std::string message)
        : type(type), message(message)
    { }

    ResultType type;
    std::string message;
};

}  // namespace imgui_markup

#endif  // IMGUI_LAYER_INCLUDE_RESULT_H_
