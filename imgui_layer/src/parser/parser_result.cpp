#include "ilpch.h"
#include "imgui_layer/parser/parser_result.h"

namespace gui
{

/* ParserPosition */
ParserPosition::ParserPosition(
    std::vector<std::string> file_stack, std::string line, size_t line_number,
    size_t start, size_t end)
    : file_stack(file_stack), line(line),
        line_number(line_number), start(start), end(end)
{ }

/* ParseResult */
ParserResult::ParserResult()
    : type_(ParserResultType::kSuccess), message_("Success"),
      position_(ParserPosition({ }, "", 0, 0, 0))
{ }

ParserResult::ParserResult(ParserResultType type)
    : type_(type), message_(""),
      position_(ParserPosition({ }, "", 0, 0, 0))
{ }

ParserResult::ParserResult(
    ParserResultType type, std::string message,
    ParserPosition position)
    : type_(type), message_(message), position_(position)
{ }

std::string ParserResult::ToString() const
{
    // TODO: Rework the function, this is currently just for debugging

    std::string message;

    for (const auto& file : this->position_.file_stack)
        message += file + "\n";

    message += "Error: " + this->message_ + "\n";
    message += "Line " + std::to_string(this->position_.line_number) +":\n";

    message += this->position_.line + "\n";

    std::string line_indicator;

    for (unsigned int i = this->position_.line.size(); i > 0; i--)
    {
        if (i - 1 >= this->position_.start && i - 1 <= this->position_.end)
            line_indicator.insert(line_indicator.begin(), '^');
        else
            line_indicator.insert(line_indicator.begin(), ' ');
    }

    message += line_indicator + "\n";

    return message;
}

ParserResult::operator bool() const
{
    return this->type_ == ParserResultType::kSuccess ? true : false;
}

}  // namespace gui
