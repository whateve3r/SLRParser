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
        yyscan_t Scanner_;

        void ScanTokens(const std::string& Input);
        Status CheckTokens();

    public:
        LexicalAnalysis(const std::string& Input);

        ~LexicalAnalysis();

        const std::vector<Token>& GetTokens() const
        {
            return Tokens_;
        }

        Status GetStatus() const
        {
            return CurrentStatus_;
        }

};

} // namespace Lexer