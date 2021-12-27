#include "ilpch.h"
#include "imgui_layer/parser/lexer.h"

#include "utility/utility.h"

namespace gui
{

/* Lexer Position */
LexerPosition::LexerPosition(
    std::vector<std::string> file_stack, std::string line, size_t line_number,
    size_t start, size_t end)
    : file_stack(file_stack), line(line),
      line_number(line_number), start(start), end(end)
{ }

/* Lexer Token */
LexerToken::LexerToken()
    : type(LexerTokenType::kUndefined), position(LexerPosition({}, "", 0, 0, 0))
{ }

LexerToken::LexerToken(const LexerTokenType type, const LexerPosition position)
    : type(type), position(position)
{ }

LexerToken::LexerToken(
    const LexerTokenType type, const LexerPosition position,
    const std::string data)
    : type(type), position(position), data(data)
{ }

/* Lexer */
void Lexer::InitFile(const std::string path)
{
    this->Reset();
    this->OpenFile(path);
}

bool Lexer::GetNextToken(LexerToken& dest)
{
    // TODO: Implement
    // TODO: Implement look ahead buffer (cache)
    dest = this->GenerateToken();

    if (dest.type == LexerTokenType::kEOF)
        return false;

    return true;
}

LexerToken Lexer::LookAhead(const int offset)
{
    // TODO: Implement
    // TOOD: Implement look ahead buffer (cache)
    return this->ConstructToken(LexerTokenType::kUndefined);
}

void Lexer::Reset()
{
    this->CloseFiles();

    this->file_stack_.clear();
}

std::string Lexer::TokenToString(LexerToken token)
{
    std::string message = "[";

    switch (token.type)
    {
    case LexerTokenType::kUndefined:
        message += "UNDEFINED";
        break;

    case LexerTokenType::kColon:
        message += "COL";
        break;

    case LexerTokenType::kComma:
        message += "COM";
        break;

    case LexerTokenType::kEqual:
        message += "EQU";
        break;

    case LexerTokenType::kBracketOpen:
        message += "BO";
        break;

    case LexerTokenType::kBracketClose:
        message += "BC";
        break;

    case LexerTokenType::kSBracketOpen:
        message += "SBO";
        break;

    case LexerTokenType::kSBracketClose:
        message += "SBC";
        break;

    case LexerTokenType::kCBracketOpen:
        message += "CBO";
        break;

    case LexerTokenType::kCBracketClose:
        message += "CBC";
        break;

    case LexerTokenType::kString:
        message += "STR=" + token.data;
        break;

    case LexerTokenType::kNumber:
        message += "NUM=" + token.data;
        break;

    case LexerTokenType::kData:
        message += "DAT=" + token.data;
        break;

    case LexerTokenType::kEOF:
        message += "EOF";
        break;

    default:
        message += "UND=" + token.data;
        break;
    }

    return message + ']';
}

/* File */
Lexer::File::File(std::string path)
    : path(path)
{
    this->file.open(this->path);
}

/* Lexer */
void Lexer::OpenFile(const std::string path)
{
    this->file_stack_.emplace_back(
        File(std::filesystem::absolute(path).string()));

    const File& file = this->file_stack_.back();

    if (!utils::PathExists(file.path))
    {
        throw FileNotFound(
            this->ConstructToken(LexerTokenType::kString, file.path));
    }

    if (!this->file_stack_.back().file.is_open())
    {
        throw UnableToOpenFile(
            this->ConstructToken(LexerTokenType::kString, path));
    }

    // Make sure that the file does not include itself
    for (unsigned int i = 0; i + 1 < this->file_stack_.size(); i++)
    {
        if (std::filesystem::equivalent(this->file_stack_[i].path, file.path))
        {
            throw FileIncludesItself(
                this->ConstructToken(LexerTokenType::kString, path));
        }
    }
}

void Lexer::CloseFiles()
{
    for (auto& f : this->file_stack_)
        f.file.close();
}

void Lexer::RemoveCurrentFile()
{
    if (this->file_stack_.empty())
        return;

    this->file_stack_.back().file.close();
    this->file_stack_.pop_back();
}

bool Lexer::GetNextChar(char& dest)
{
    if (this->file_stack_.empty())
        return false;

    File& file = this->file_stack_.back();

    if (file.position_in_line >= file.current_line.size())
    {
        file.position_in_line = 0;
        file.line_number++;

        if (!std::getline(file.file, file.current_line))
            return false;

        if (file.line_number != 1)
        {
            dest = '\n';
            return true;
        }
    }

    dest = file.current_line[file.position_in_line++];

    return true;
}

char Lexer::GetCurrentChar(size_t offset) const
{
    if (this->file_stack_.empty())
        return 0;

    const File& file = this->file_stack_.back();

    if (file.position_in_line + offset - 1 < 0)
        return 0;
    if (file.position_in_line + offset - 1 >= file.current_line.size())
        return 0;

    return file.current_line[file.position_in_line + offset - 1];
}

LexerToken Lexer::GenerateToken()
{
    char c;
    if (!this->GetNextChar(c))
    {
        this->RemoveCurrentFile();

        if (this->file_stack_.empty())
            return this->ConstructToken(LexerTokenType::kEOF);

        return this->GenerateToken();
    }

    if (std::isspace(c))
        return this->GenerateToken();
    else if (this->IsComment())
    {
        this->SkipComment();
        return this->GenerateToken();
    }
    else if(c == ':')
        return this->ConstructToken(LexerTokenType::kColon);
    else if(c == ',')
        return this->ConstructToken(LexerTokenType::kComma);
    else if(c == '=')
        return this->ConstructToken(LexerTokenType::kEqual);
    else if(c == '(')
        return this->ConstructToken(LexerTokenType::kBracketOpen);
    else if(c == ')')
        return this->ConstructToken(LexerTokenType::kBracketClose);
    else if(c == '[')
        return this->ConstructToken(LexerTokenType::kSBracketOpen);
    else if(c == ']')
        return this->ConstructToken(LexerTokenType::kSBracketClose);
    else if(c == '{')
        return this->ConstructToken(LexerTokenType::kCBracketOpen);
    else if(c == '}')
        return this->ConstructToken(LexerTokenType::kCBracketClose);
    else if (c == '@')
        return this->ProcessLexerInstruction();
    else if(c == '"')
        return this->CreateString();
    else if (std::isdigit(c))
        return this->CreateNumber();
    else if (std::isalpha(c) || std::isdigit(c) || c == '_' || c == '.')
        return this->CreateData();
    else
        throw InvalidSymbol(this->ConstructToken(LexerTokenType::kUndefined));

    return this->ConstructToken(LexerTokenType::kUndefined);
}

bool Lexer::IsComment() const
{
    if (this->file_stack_.empty())
        return false;

    const File& file = this->file_stack_.back();

    if (this->GetCurrentChar() == '#')
        return true;

    if (this->GetCurrentChar()   == '/' &&
        (this->GetCurrentChar(1) == '/' || this->GetCurrentChar(1) == '*'))
    {
        return true;
    }

    return false;
}

void Lexer::SkipComment()
{
    bool multiline = false;

    if (this->GetCurrentChar() == '/' && this->GetCurrentChar(1) == '*')
        multiline = true;

    char c;
    while (this->GetNextChar(c))
    {
        if (!multiline && c == '\n')
            return;

        if (multiline && c == '/' && this->GetCurrentChar(-1) == '*')
            return;
    }
}

LexerToken Lexer::CreateString()
{
    std::string value;
    size_t start_pos = this->GetCurrentPosition();

    char c;
    while (this->GetNextChar(c))
    {
        if (this->GetCurrentChar() == '"' && this->GetCurrentChar(-1) != '\\')
        {
            return this->ConstructToken(LexerTokenType::kString, value,
                                        start_pos, this->GetCurrentPosition());
        }

        value += c;
    }

    throw UnexpectedEndOfString(
        this->ConstructToken(LexerTokenType::kString, value,
                             start_pos, this->GetCurrentPosition()));
}

LexerToken Lexer::CreateNumber()
{
    std::string value;
    value += this->GetCurrentChar();

    size_t start_pos = this->GetCurrentPosition();
    size_t dot_count = 0;

    char c;
    while (this->GetNextChar(c))
    {
        if (this->IsComment())
        {
            this->SkipComment();
            break;
        }

        if (c == '.')
            dot_count++;

        value += c;

        const char next_char = this->GetCurrentChar(1);
        if (!isdigit(next_char) && next_char != '.')
            break;
    }

    if (dot_count > 1)
    {
        throw InvalidNumber(
            this->ConstructToken(LexerTokenType::kNumber, value,
                                start_pos, this->GetCurrentPosition()));
    }

    return this->ConstructToken(LexerTokenType::kNumber, value,
                            start_pos, this->GetCurrentPosition());
}

LexerToken Lexer::CreateData()
{
    std::string value;
    value += this->GetCurrentChar();

    size_t start_pos = this->GetCurrentPosition();

    char c;
    while (this->GetNextChar(c))
    {
        if (this->IsComment())
        {
            this->SkipComment();
            break;
        }

        value += c;

        const char next_char = this->GetCurrentChar(1);
        if (!std::isalpha(next_char) && !std::isdigit(next_char) &&
            next_char != '_' && next_char != '.')
        {
            break;
        }
    }

    return this->ConstructToken(LexerTokenType::kData, value,
                                start_pos, this->GetCurrentPosition());
}

LexerToken Lexer::ProcessLexerInstruction()
{
    std::string instruction;

    char c;
    while (this->GetNextChar(c))
    {
        if (std::isspace(c))
            break;

        instruction += c;
    }

    if (instruction == "include")
        return this->ProcessIncludeInstruction();

    return this->ConstructToken(LexerTokenType::kUndefined);
}

LexerToken Lexer::ProcessIncludeInstruction()
{
    LexerToken arg = this->GenerateToken();

    if (arg.type != LexerTokenType::kString)
        throw WrongIncludeArgument(arg);

    const std::string path = this->GetCurrentDirectory() + '/' + arg.data;

    this->OpenFile(path);

    return this->GenerateToken();
}

LexerToken Lexer::ConstructToken(LexerTokenType type) const
{
    return this->ConstructToken(type, "");
}

LexerToken Lexer::ConstructToken(LexerTokenType type, std::string data) const
{
    if (this->file_stack_.empty())
        return LexerToken(type, LexerPosition({}, "", 0, 0, 0));

    const File& file = this->file_stack_.back();

    return LexerToken(type,
                      LexerPosition(this->ConvertFileStack(), file.current_line,
                                    file.line_number,
                                    file.position_in_line,
                                    file.position_in_line + 1),
                      data);
}

LexerToken Lexer::ConstructToken(LexerTokenType type, std::string data,
                                 size_t start, size_t end) const
{
    if (this->file_stack_.empty())
        return LexerToken(type, LexerPosition({}, "", 0, 0, 0));

    const File& file = this->file_stack_.back();

    return LexerToken(type,
                      LexerPosition(this->ConvertFileStack(), file.current_line,
                                    file.line_number, start, end),
                      data);
}

std::vector<std::string> Lexer::ConvertFileStack() const
{
    std::vector<std::string> result;
    for (const auto& file : this->file_stack_)
        result.push_back(file.path);
    return result;
}


size_t Lexer::GetCurrentPosition() const
{
    if (this->file_stack_.empty())
        return 0;

    const File& file = this->file_stack_.back();

    return file.position_in_line == 0 ? 0 : file.position_in_line - 1;
}

std::string Lexer::GetCurrentDirectory() const
{
    if (this->file_stack_.empty())
        return std::string();

    return std::filesystem::path(
        this->file_stack_.back().path).parent_path().string();
}

}  // namespace gui
