#pragma once

#include <vector>
#include <string>

#include "tokens.hpp"
#include "status.hpp"
#include <FlexLexer.h>

namespace SLR::Lexer {

class LexicalAnalysis
{
    private:
        std::vector<Token> Tokens_;
        Status CurrentStatus_;

        yyFlexLexer Scanner_;
        std::ostream& Output_;

        void ScanTokens();
        Status CheckTokens();

    public:
        LexicalAnalysis(std::istream& Input, std::ostream& Output);

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