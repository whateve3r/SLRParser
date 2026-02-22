#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <sstream>
#include <map>
#include <string>


#include "status.hpp"
#include "tokens.hpp"
#include "grammar.hpp"

class SyntaxAnalysis
{
    private:
        static inline const std::map<int, int> TokenToCol = 
        {
            {TOKEN_ID,       0},

            {TOKEN_PLUS,     1},
            {TOKEN_MINUS,    2},

            {TOKEN_MULT,     3},
            {TOKEN_DIV,      4},

            {TOKEN_LBRACKET, 5},
            {TOKEN_RBRACKET, 6},

            {TOKEN_EOF,     10}
        };


        static constexpr int COLS = 11;
        static constexpr int STATES = 18;

        static constexpr std::array<std::array<int, COLS>, STATES> SLRTable = 
        {{
            { 5,  0,  6,  0,  0,  4,  0,  1,  2,  3,  0 },
            { 0,  7, 10,  0,  0,  0,  0,  0,  0,  0, 100},
            { 0, -3, -3,  8,  9,  0, -3,  0,  0,  0, -3 }, 
            { 0, -6, -6, -6, -6,  0, -6,  0,  0,  0, -6 }, 
            { 5,  0,  6,  0,  0,  4,  0, 13,  2,  3,  0 },
            { 0, -8, -8, -8, -8,  0, -8,  0,  0,  0, -8 },
            { 5,  0,  6,  0,  0,  4,  0,  0,  0, 12,  0 },
            { 5,  0,  6,  0,  0,  4,  0,  0, 11,  3,  0 },
            { 5,  0,  6,  0,  0,  4,  0,  0,  0, 15,  0 },
            { 5,  0,  6,  0,  0,  4,  0,  0,  0, 16,  0 },
            { 5,  0,  6,  0,  0,  4,  0,  0, 17,  3,  0 },
            { 0, -1, -1,  8,  9,  0, -1,  0,  0,  0, -1 },
            { 0, -9, -9, -9, -9,  0, -9,  0,  0,  0, -9 }, 
            { 0,  7, 10,  0,  0,  0, 14,  0,  0,  0,  0 },
            { 0, -7, -7, -7, -7,  0, -7,  0,  0,  0, -7 }, 
            { 0, -4, -4, -4, -4,  0, -4,  0,  0,  0, -4 },
            { 0, -5, -5, -5, -5,  0, -5,  0,  0,  0, -5 }, 
            { 0, -2, -2,  8,  9,  0, -2,  0,  0,  0, -2 }  
        }};


        int getColIndex(int token)
        {
            auto TokenToPtr = TokenToCol.find(token);

            assert(TokenToPtr != TokenToCol.end());

            return TokenToPtr->second;
        }

        void recordStep(const std::vector<int>& stack, const std::vector<Token>& input, size_t cursor, std::string ActionString, std::stringstream& buffer)
        {
            buffer << "STACK:  $";

            for (size_t i = 0; i < stack.size(); i++)
            {
                buffer << stack[i];
            }

            buffer << std::endl;


            buffer << "INPUT:  ";

            for (size_t j = cursor; j < input.size(); j++)
            {
                buffer << input[j].attribute;
            }

            buffer << std::endl;

            buffer << "ACTION: " << ActionString << std::endl;
        }

    public:
        Status SLRParser(const std::vector<Token>& Tokens)
        {
            std::vector<int> Stack;
            Stack.push_back(0);

            std::stringstream buffer;

            size_t index = 0;

            while (true)
            {
                int Lookahead = Tokens[index].TokenType;

                int CurrentState = Stack.back();
                int CurrentCol = getColIndex(Lookahead);

                int action = SLRTable.at(CurrentState).at(CurrentCol);

                if (action == 0)
                {
                    std::cerr << "ERROR: Syntax Error" << std::endl;
                    return Status::Syntax_Error;
                }

                if (action > 0 && action != 100)
                {
                    recordStep(Stack, Tokens, index, "Shift", buffer);
                    Stack.push_back(action);
                    index++;
                }


                if (action < 0)
                {
                    recordStep(Stack, Tokens, index, "Reduce", buffer);

                    Rule CurrentRule = grammar[abs(action)];

                    int LHS = CurrentRule.LHS;
                    int len = CurrentRule.len;

                    for (int i = 0; i < len; i++)
                    {
                        Stack.pop_back();
                    }

                    int StateBefore = Stack.back();

                    int NewState = SLRTable[StateBefore][LHS];

                    Stack.push_back(NewState);
                }

                
                if (action == 100)
                {
                    recordStep(Stack, Tokens, index, "Accept", buffer);

                    std::cout << buffer.str();

                    return Status::Success;
                }

            }

        }
        
};