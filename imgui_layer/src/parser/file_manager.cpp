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

FileManager& FileManager::Get()
{
    static FileManager instance;
    return instance;
}

bool FileManager::IMPLLoadFromFile(const std::string path, GlobalObject& dest)
{
    std::ifstream file(path);

    if (!file.is_open())
        // TOOD: Error handling
        return false;

    std::stringstream data;
    data << file.rdbuf();

    file.close();

    return FileManager::LoadFromData(data.str(), dest);
}

bool FileManager::IMPLLoadFromData(const std::string data, GlobalObject& dest)
{
    gui::Lexer lexer(data);
    gui::Parser parser(lexer.GetTokens());
    gui::Interpreter interpreter(parser.Parse());

    dest = interpreter.CreateGlobalObject();

    // TOOD: Error handling

    return true;
}

}  // namespace gui
