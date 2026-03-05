#include <iostream>
#include "LexicalAnalysis.hpp"

namespace SLR::Lexer {

LexicalAnalysis::LexicalAnalysis(std::istream& Input, std::ostream& Output) : Scanner_(&Input), Output_(Output)
{
    ScanTokens();
    CurrentStatus_ = CheckTokens();
}

void LexicalAnalysis::ScanTokens()
{
    TokenType CurrentTokenType;

    while( (CurrentTokenType = static_cast<TokenType>(Scanner_.yylex())) != TokenType::END_OF_FILE)
    {
        std::string CurrentAttribute = Scanner_.YYText();
        Tokens_.push_back({CurrentTokenType, CurrentAttribute});
    }

    Tokens_.push_back({TokenType::END_OF_FILE, "$"});
}

Status LexicalAnalysis::CheckTokens()
{
    for (size_t i = 0; i < Tokens_.size(); i++)
    {
        if (Tokens_[i].Type == TokenType::UNKNOWN)
        {
            Output_ << "ERROR: Unknown Symbol: " << Tokens_[i].Attribute << std::endl;
            return Status::LEXICAL_ERROR;
        }
    }

    Output_ << "Tokens scanned successfully!" << std::endl;
    return Status::SUCCESS;
}

}