#pragma once

#include <vector>
#include <array>
#include <string>


#include "status.hpp"
#include "tokens.hpp"
#include "grammar.hpp"

namespace SLR::Parser {

class SyntaxAnalysis
{
    private:
        size_t GetColIndex(TokenType Token);

        void RecordStep(const std::vector<size_t>& Stack, const std::vector<Token>& Input, size_t Cursor, const std::string& ActionString, std::stringstream& Buffer);

    public:
        enum class Action
        {
            SHIFT,
            REDUCE,
            ACCEPT,
            ERROR
        };

        struct ActionCell
        {
            Action Action_;
            size_t Value;
        };

        Status SLRParser(const std::vector<Token>& Tokens);
};

} // namespace Parser