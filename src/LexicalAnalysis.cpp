#include <iostream>
#include "LexicalAnalysis.hpp"

SLR::TokenType yylex(yyscan_t yyscanner);
char* yyget_text(yyscan_t yyscanner);

YY_BUFFER_STATE yy_scan_string(const char* str, yyscan_t yyscanner);
void yy_delete_buffer(YY_BUFFER_STATE buffer, yyscan_t yyscanner);
                                                    
int yylex_init(yyscan_t* ptr_to_yyscanner);
int yylex_destroy(yyscan_t yyscanner);


namespace SLR::Lexer {

LexicalAnalysis::LexicalAnalysis(const std::string& Input)
{
    yylex_init(&Scanner_);
    ScanTokens(Input);
    CurrentStatus_ = CheckTokens();
}

LexicalAnalysis::~LexicalAnalysis()
{
    yylex_destroy(Scanner_);
}

void LexicalAnalysis::ScanTokens(const std::string& Input)
{
    YY_BUFFER_STATE InputBuffer = yy_scan_string(Input.c_str(), Scanner_);

    SLR::TokenType CurrentTokenType = yylex(Scanner_);
    std::string CurrentAttribute = std::string(yyget_text(Scanner_));

    while(CurrentTokenType != TokenType::END_OF_FILE)
    {
        Tokens_.push_back({CurrentTokenType, CurrentAttribute});
        CurrentTokenType = yylex(Scanner_);
        CurrentAttribute = std::string(yyget_text(Scanner_));
    }

    Tokens_.push_back({TokenType::END_OF_FILE, "$"});

    yy_delete_buffer(InputBuffer, Scanner_);
}

Status LexicalAnalysis::CheckTokens()
{
    for (size_t i = 0; i < Tokens_.size(); i++)
    {
        if (Tokens_[i].Type == TokenType::UNKNOWN)
        {
            std::cerr << "ERROR: Unknown Symbol: " << Tokens_[i].Attribute << std::endl;
            return Status::LEXICAL_ERROR;
        }
    }

    return Status::SUCCESS;
}

}