#include <cstdlib>
#include "LexicalAnalysis.hpp"
#include "SyntaxAnalysis.hpp"


int main()
{
    LexicalAnalysis Lexer;

    if (Lexer.getStatus() != Status::Success)
    {
        return EXIT_FAILURE;
    }

    SyntaxAnalysis SLRParser;

    Status ParserStatus = SLRParser.SLRParser(Lexer.getTokens());

    if (ParserStatus != Status::Success)
    {
        return EXIT_FAILURE;
    }
}