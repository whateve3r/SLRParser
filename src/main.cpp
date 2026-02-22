#include <iostream>
#include <cstdlib>
#include "LexicalAnalysis.hpp"
#include "SyntaxAnalysis.hpp"


int main()
{

    std::string input;

    std::getline(std::cin, input);

    SLR::Lexer::LexicalAnalysis Lexer(input);

    if (Lexer.getStatus() != SLR::Status::Success)
    {
        return EXIT_FAILURE;
    }

    SLR::Parser::SyntaxAnalysis SLRParser;

    SLR::Status ParserStatus = SLRParser.SLRParser(Lexer.getTokens());

    if (ParserStatus != SLR::Status::Success)
    {
        return EXIT_FAILURE;
    }
}