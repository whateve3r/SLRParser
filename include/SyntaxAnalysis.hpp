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

class SyntaxAnalysis
{
    private:
        struct Rule
        {
            int LHS;           // Left Hand Side - код нетерминала слева (столбец в таблице)
            int len;           // Длина правой части, сколько символов удалять
        };

        static constexpr std::array<Rule, 6> grammar =
        {{
            {0, 0},            
            {4, 3},
            {4, 1},           
            {5, 3},
            {5, 1},
            {6, 1}
        }};

        static inline const std::map<int, int> TokenToCol = 
        {
            {TOKEN_ID, 0},
            {TOKEN_PLUS, 1},
            {TOKEN_MULT, 2},
            {TOKEN_EOF, 3}
        };


        static constexpr int COLS = 7;
        static constexpr int STATES = 9;

        static constexpr std::array<std::array<int, COLS>, STATES> SLRTable = 
        {{
            {4, 0, 0, 0, 1, 2,    3},
            {0, 5, 0, 100, 0, 0,  0},
            {0, -2, 6, -2, 0, 0,  0},
            {0, -4, -4, -4, 0, 0, 0},
            {0, -5, -5, -5, 0, 0, 0},
            {4, 0, 0, 0, 0, 7,    3},
            {4, 0, 0, 0, 0, 0,    8},
            {0, -1, 6, -1, 0, 0,  0},
            {0, -3, -3, -3, 0, 0, 0}
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