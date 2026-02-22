#include <iostream>
#include "LexicalAnalysis.hpp"

int yylex(yyscan_t yyscanner);
char* yyget_text(yyscan_t yyscanner);

YY_BUFFER_STATE yy_scan_string(const char* str, yyscan_t yyscanner);
void yy_delete_buffer(YY_BUFFER_STATE buffer, yyscan_t yyscanner);
                                                    
int yylex_init(yyscan_t* ptr_to_yyscanner);
int yylex_destroy(yyscan_t yyscanner);


namespace SLR::Lexer {

LexicalAnalysis::LexicalAnalysis(const std::string& input)
{
    yylex_init(&scanner_);
    scanTokens(input);
    CurrentStatus_ = checkTokens();
}

LexicalAnalysis::~LexicalAnalysis()
{
    yylex_destroy(scanner_);
}

void LexicalAnalysis::scanTokens(const std::string& input)
{
    YY_BUFFER_STATE InputBuffer = yy_scan_string(input.c_str(), scanner_);

    int CurrentTokenType = yylex(scanner_);
    std::string CurrentAttribute = std::string(yyget_text(scanner_));

    while(CurrentTokenType != 0)
    {
        Tokens_.push_back({CurrentTokenType, CurrentAttribute});
        CurrentTokenType = yylex(scanner_);
        CurrentAttribute = std::string(yyget_text(scanner_));
    }

    Tokens_.push_back({0, "$"});

    yy_delete_buffer(InputBuffer, scanner_);
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

}