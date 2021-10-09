#include "ilpch.h"
#include "parser/file_manager.h"

#include "parser/lexer.h"
#include "parser/parser.h"
#include "parser/interpreter.h"

namespace gui
{

bool FileManager::LoadFromFile(const std::string path, GlobalObject& dest)
{
    return FileManager::Get().IMPLLoadFromFile(path, dest);
}

bool FileManager::LoadFromData(const std::string data, GlobalObject& dest)
{
    return FileManager::Get().IMPLLoadFromData(data, dest);
}

ParserError FileManager::GetLastError()
{
    return FileManager::Get().IMPLGetLastError();
}

FileManager& FileManager::Get()
{
    static FileManager instance;
    return instance;
}

bool FileManager::IMPLLoadFromFile(const std::string path, GlobalObject& dest)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        this->last_error_ = ParserError(ParserErrorType::kUnableToOpenFile,
            "Unable to open file \"" + path + "\"");

        return false;
    }

    std::stringstream data;
    data << file.rdbuf();

    file.close();

    return FileManager::LoadFromData(data.str(), dest);
}

bool FileManager::IMPLLoadFromData(const std::string data, GlobalObject& dest)
{
    dest.Reset();

    gui::Lexer lexer(data);

    gui::Parser parser(lexer.GetTokens(), data);

    std::vector<std::shared_ptr<Node>> nodes;
    if (!parser.Parse(nodes))
    {
        this->last_error_ = parser.GetLastError();
        return false;
    }

    gui::Interpreter interpreter(nodes, data);

    if (!interpreter.CreateGlobalObject(dest))
    {
        this->last_error_ = interpreter.GetLastError();
        return false;
    }

    return true;
}

ParserError FileManager::IMPLGetLastError()
{
    return this->last_error_;
}

}  // namespace gui
