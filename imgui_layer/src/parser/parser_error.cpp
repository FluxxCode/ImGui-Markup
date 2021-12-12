#include "ilpch.h"
#include "imgui_layer/parser/parser_error.h"

namespace gui
{

Position::Position()
    : start_(0), end_(0)
{ }

Position::Position(const size_t start)
    : start_(start), end_(start + 1)
{ }

Position::Position(const size_t start, const size_t end)
    : start_(start), end_(end)
{ }

ParserError::ParserError()
    : type_(ParserErrorType::kUndefined), position_(Position(0)), message_("")
{ }

ParserError::ParserError(
    const ParserErrorType type,
    const std::string message)
    : type_(type), position_(Position(0)), message_(message)
{ }

ParserError::ParserError(
    const ParserErrorType type,
    const Position position,
    const std::string message,
    const std::string& data)
    : type_(type), position_(position), message_(message)
{
    this->GetErrorPositionInLine(data);
}

std::string ParserError::ToString() const
{
    std::string message = "Error: " + this->message_;

    if (this->line_.empty())
        return message;

    message += "\nLine: " + std::to_string(this->line_number_) + "\n" +
        this->line_ + "\n";

    const size_t error_size = this->position_.end_ - this->position_.start_;
    for (unsigned int i = 0; i < this->pos_in_line_ + error_size; i++)
    {
        if (i < this->pos_in_line_)
            message += ' ';
        else
            message += '^';

        if (i == this->line_.size() - 1)
            break;
    }

    return message;
}

bool ParserError::GetErrorPositionInLine(const std::string& data)
{
    size_t char_count = 0;
    size_t line_count = 0;

    std::string line;
    std::istringstream iss(data);
    while (getline(iss, line))
    {
        if (char_count <= this->position_.start_ &&
            char_count + line.size() + 1 > this->position_.start_)
        {
            this->line_number_ = line_count + 1;
            this->pos_in_line_ = this->position_.start_ - char_count;
            this->line_ = line;
            return true;
        }

        // We will add 1 because of the '\n'
        char_count += line.size() + 1;
        line_count++;
    }

    return false;
}

}  // namespace gui
