#pragma once

#include <vector>
#include <string>

#include "tokens.hpp"
#include "status.hpp"

using yyscan_t = void*; // flex instance; ptr to flex struct (how to work with input string)
using YY_BUFFER_STATE = struct yy_buffer_state*; // ptr to struct of an input string

namespace SLR::Lexer {

class LexicalAnalysis
{
    private:
        std::vector<Token> Tokens_;
        Status CurrentStatus_;
        yyscan_t scanner_;

        void scanTokens(const std::string& input);
        Status checkTokens();

    public:
        LexicalAnalysis(const std::string& input);

        ~LexicalAnalysis();

        const std::vector<Token>& getTokens() const
        {
            return Tokens_;
        }

        Status getStatus() const
        {
            return CurrentStatus_;
        }

};

}