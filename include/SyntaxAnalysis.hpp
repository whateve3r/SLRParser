#pragma once

#include <vector>
#include <array>
#include <map>
#include <string>


#include "status.hpp"
#include "tokens.hpp"
#include "grammar.hpp"

namespace SLR::Parser {

class SyntaxAnalysis
{
    private:
        static const std::map<int, int> TokenToCol;

        static constexpr int COLS = 11;
        static constexpr int STATES = 18;
        static const std::array<std::array<int, COLS>, STATES> SLRTable;

        int getColIndex(int token);

        void recordStep(const std::vector<int>& stack, const std::vector<Token>& input, size_t cursor, std::string ActionString, std::stringstream& buffer);

    public:
        Status SLRParser(const std::vector<Token>& Tokens);
};

}