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
        std::vector<Token> Tokens;
        Status CurrentStatus;
        yyscan_t scanner;

        void scanTokens()
        {
            int CurrentTokenType = yylex(this->scanner);
            std::string CurrentAttribute = std::string(yyget_text(this->scanner));

            while(CurrentTokenType != 0)
            {
                Tokens.push_back({CurrentTokenType, CurrentAttribute});
                CurrentTokenType = yylex(this->scanner);
                CurrentAttribute = std::string(yyget_text(this->scanner));
            }

            Tokens.push_back({0, "$"});
        }

        Status checkTokens()
        {
            for (size_t i = 0; i < Tokens.size(); i++)
            {
                if (Tokens[i].TokenType == UNKNOWN_TOKEN)
                {
                    std::cerr << "ERROR: Unknown Symbol: " << Tokens[i].attribute << std::endl;
                    return Status::Lexical_Error;
                }
            }

            return Status::Success;
        }

    public:
        LexicalAnalysis()
        {
            yylex_init(&scanner);
            scanTokens();
            CurrentStatus = checkTokens();
        }

        ~LexicalAnalysis()
        {
            yylex_destroy(scanner);
        }

        const std::vector<Token>& getTokens() const
        {
            return Tokens;
        }

        Status getStatus() const
        {
            return CurrentStatus;
        }

};