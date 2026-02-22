#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "tokens.hpp"
#include "status.hpp"

using yyscan_t = void*;

int yylex(yyscan_t yyscanner);
char* yyget_text(yyscan_t yyscanner);
                                                    
int yylex_init(yyscan_t* ptr_to_yyscanner);
int yylex_destroy(yyscan_t yyscanner);



class LexicalAnalysis
{
    private:
        std::vector<Token> Tokens_;
        Status CurrentStatus_;
        yyscan_t scanner_;

        void scanTokens()
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

        Status checkTokens()
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

    public:
        LexicalAnalysis()
        {
            yylex_init(&scanner_);
            scanTokens();
            CurrentStatus_ = checkTokens();
        }

        ~LexicalAnalysis()
        {
            yylex_destroy(scanner_);
        }

        const std::vector<Token>& getTokens() const
        {
            return Tokens_;
        }

        Status getStatus() const
        {
            return CurrentStatus_;
        }

};