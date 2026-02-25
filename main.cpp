#include <iostream>
#include <cstdlib>
#include "LexicalAnalysis.hpp"
#include "SyntaxAnalysis.hpp"


int main()
{

    std::string input;

    std::getline(std::cin, input);

    SLR::Lexer::LexicalAnalysis Lexer(input);

    if (Lexer.GetStatus() != SLR::Status::SUCCESS)
    {
        return EXIT_FAILURE;
    }

    SLR::Parser::SyntaxAnalysis SLRParser;

    SLR::Status ParserStatus = SLRParser.SLRParser(Lexer.GetTokens());

    if (ParserStatus != SLR::Status::SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}