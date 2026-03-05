#include <iostream>
#include <cstdlib>
#include <fstream>
#include "LexicalAnalysis.hpp"
#include "SyntaxAnalysis.hpp"


int main(const int argc, const char* argv[])
{
    std::ifstream InputFile;
    std::ofstream OutputFile;

    std::istream* Input = &std::cin;

    if (argc >= 2)
    {
        InputFile.open(argv[1]);
        Input = &InputFile;
    }

    std::string FileName = (argc >= 3) ? argv[2] : "../Result.log";
    OutputFile.open(FileName);


    SLR::Lexer::LexicalAnalysis Lexer(*Input, OutputFile);

    if (Lexer.GetStatus() != SLR::Status::SUCCESS)
    {
        return EXIT_FAILURE;
    }

    SLR::Parser::SyntaxAnalysis SLRParser;

    SLR::Status ParserStatus = SLRParser.SLRParser(Lexer.GetTokens(), OutputFile);

    if (ParserStatus != SLR::Status::SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}