#include "ilpch.h"
#include "imgui_layer/parser/parser.h"

#include "imgui_layer/parser/lexer.h"

#include <iostream>

namespace gui
{

/* Parser */
ParserResult Parser::ParseFile(const std::string file, GlobalObject& dest)
{
    // NOTE: This is all just for debugging and will be removed later

    try
    {
        Lexer lexer;
        lexer.InitFile(file);

        LexerToken token;
        while (lexer.GetNextToken(token))
        {
            std::cout << Lexer::TokenToString(token) << ", ";
            std::flush(std::cout);
        }
    }
    catch(const LexerException& e)
    {
        std::cerr << "\nERROR: " << e.message << ", Data: \"" <<
            e.token.data << "\"" << std::endl;

        std::cerr << "FILE STACK:\n";
        for (const auto& i : e.token.position.file_stack)
            std::cout << i << std::endl;
    }

    return ParserResult(ParserResultType::kSuccess);
}

}  // namespace gui
