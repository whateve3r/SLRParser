#include <iostream>
#include "LexicalAnalysis.hpp"


int yylex(yyscan_t yyscanner);
char* yyget_text(yyscan_t yyscanner);
                                                    
int yylex_init(yyscan_t* ptr_to_yyscanner);
int yylex_destroy(yyscan_t yyscanner);

LexicalAnalysis::LexicalAnalysis()
{
    yylex_init(&scanner_);
    scanTokens();
    CurrentStatus_ = checkTokens();
}

LexicalAnalysis::~LexicalAnalysis()
{
    yylex_destroy(scanner_);
}

void LexicalAnalysis::scanTokens()
{
    int CurrentTokenType = yylex(scanner_);
    std::string CurrentAttribute = std::string(yyget_text(scanner_));

    while(CurrentTokenType != 0)
    {
        Tokens_.push_back({CurrentTokenType, CurrentAttribute});
        CurrentTokenType = yylex(scanner_);
        CurrentAttribute = std::string(yyget_text(scanner_));
    }

    Tokens_.push_back({0, "$"});
}

Status LexicalAnalysis::checkTokens()
{
    for (size_t i = 0; i < Tokens_.size(); i++)
    {
        if (Tokens_[i].TokenType == UNKNOWN_TOKEN)
        {
            std::cerr << "ERROR: Unknown Symbol: " << Tokens_[i].attribute << std::endl;
            return Status::Lexical_Error;
        }
    }

    return Status::Success;
}