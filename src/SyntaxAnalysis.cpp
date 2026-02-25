#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

#include "SyntaxAnalysis.hpp"

namespace SLR::Parser {

namespace {

constexpr size_t COLS_ACTION = 8;
constexpr size_t COLS_GOTO = 3;
constexpr size_t STATES = 18;

constexpr size_t ERR_STATE = std::numeric_limits<size_t>::max();


#define S(Value) {SyntaxAnalysis::Action::SHIFT,  Value}
#define R(Value) {SyntaxAnalysis::Action::REDUCE, Value}
#define ERR      {SyntaxAnalysis::Action::ERROR,      0}
#define ACC      {SyntaxAnalysis::Action::ACCEPT,     0}

constexpr std::array<std::array<SyntaxAnalysis::ActionCell, COLS_ACTION>, STATES> ActionTable = 
{{  // id     +      -      *      /      (      )       $
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 0
    {{ ERR,   S(7),  S(10), ERR,   ERR,   ERR,   ERR,   ACC  }}, // State 1
    {{ ERR,   R(3),  R(3),  S(8),  S(9),  ERR,   R(3),  R(3) }}, // State 2
    {{ ERR,   R(6),  R(6),  R(6),  R(6),  ERR,   R(6),  R(6) }}, // State 3
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 4
    {{ ERR,   R(8),  R(8),  R(8),  R(8),  ERR,   R(8),  R(8) }}, // State 5
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 6
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 7
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 8
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 9
    {{ S(5),  ERR,   S(6),  ERR,   ERR,   S(4),  ERR,   ERR  }}, // State 10
    {{ ERR,   R(1),  R(1),  S(8),  S(9),  ERR,   R(1),  R(1) }}, // State 11
    {{ ERR,   R(9),  R(9),  R(9),  R(9),  ERR,   R(9),  R(9) }}, // State 12
    {{ ERR,   S(7),  S(10), ERR,   ERR,   ERR,   S(14), ERR  }}, // State 13
    {{ ERR,   R(7),  R(7),  R(7),  R(7),  ERR,   R(7),  R(7) }}, // State 14
    {{ ERR,   R(4),  R(4),  R(4),  R(4),  ERR,   R(4),  R(4) }}, // State 15
    {{ ERR,   R(5),  R(5),  R(5),  R(5),  ERR,   R(5),  R(5) }}, // State 16
    {{ ERR,   R(2),  R(2),  S(8),  S(9),  ERR,   R(2),  R(2) }}  // State 17
}};

#undef S
#undef R
#undef ERR
#undef ACC

constexpr std::array<std::array<size_t, COLS_GOTO>, STATES> GOTOTable
{{
    //      E          T           F
    {{      1    ,     2    ,     3      }}, // State 0
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 1
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 2
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 3
    {{     13    ,     2    ,    3       }}, // State 4
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 5
    {{  ERR_STATE, ERR_STATE,    12      }}, // State 6
    {{  ERR_STATE,    11    ,     3      }}, // State 7
    {{  ERR_STATE, ERR_STATE,    15      }}, // State 8
    {{  ERR_STATE, ERR_STATE,    16      }}, // State 9
    {{  ERR_STATE,    17    ,     3      }}, // State 10
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 11
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 12
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 13
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 14
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 15
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 16
    {{  ERR_STATE, ERR_STATE, ERR_STATE  }}, // State 17
}};

} // namespace


void SyntaxAnalysis::RecordStep(const std::vector<size_t>& Stack, const std::vector<Token>& Input, size_t Cursor, const std::string& ActionString, std::stringstream& Buffer)
{
    std::string Stack_Str;

    for (size_t i = 0; i < Stack.size(); i++) 
    {
        Stack_Str += std::to_string(Stack[i]) + " ";
    }

    std::string Input_Str;

    for (size_t j = Cursor; j < Input.size(); j++) 
    {
        Input_Str += Input[j].Attribute; 
    }

    Buffer << "| "  << std::left << std::setw(20)  << Stack_Str 
           << " | " << std::left << std::setw(15)  << Input_Str 
           << " | " << ActionString << "\n";
}

Status SyntaxAnalysis::SLRParser(const std::vector<Token>& Tokens)
{
    std::vector<size_t> Stack;
    Stack.push_back(0);

    std::stringstream Buffer;

    Buffer << "| " << std::left << std::setw(20) << "STACK" 
           << " | " << std::left << std::setw(15) << "INPUT" 
           << " | ACTION \n";

    size_t Index = 0;

    while (true)
    {
        if (Index >= Tokens.size())
        {
            std::cerr << "ERROR: Unexpected end of input (missing EOF token '$')" << std::endl;
            return Status::SYNTAX_ERROR;
        }

        size_t CurrentState = Stack.back();
        size_t CurrentCol   = static_cast<size_t>(Tokens[Index].Type);

        ActionCell Cell = ActionTable[CurrentState][CurrentCol];

        switch(Cell.Action_)
        {
            case SyntaxAnalysis::Action::ERROR:
                std::cerr << "ERROR: Syntax Error" << std::endl;
                return Status::SYNTAX_ERROR;


            case SyntaxAnalysis::Action::SHIFT:
                RecordStep(Stack, Tokens, Index, "Shift " + std::to_string(Cell.Value), Buffer);
                Stack.push_back(Cell.Value);
                Index++;
                break;


            case SyntaxAnalysis::Action::REDUCE:
            {
                RecordStep(Stack, Tokens, Index, "Reduce " + std::to_string(Cell.Value), Buffer);

                Rule CurrentRule = Grammar[Cell.Value];

                NonTerminals LHS = CurrentRule.LHS;
                size_t Len = CurrentRule.Len;

                for (size_t i = 0; i < Len; i++)
                {
                    Stack.pop_back();
                }

                size_t StateBefore = Stack.back();

                size_t NewState = GOTOTable[StateBefore][static_cast<size_t>(LHS)];

                if (NewState == ERR_STATE)
                {
                    std::cerr << "ERROR: Syntax Error" << std::endl;
                    return Status::SYNTAX_ERROR;
                }

                Stack.push_back(NewState);
                break;
            }

            case SyntaxAnalysis::Action::ACCEPT:
            {
                RecordStep(Stack, Tokens, Index, "Accept",  Buffer);

                std::ofstream outfile("OutputTable.txt");
                outfile << Buffer.str();

                return Status::SUCCESS;
            }
        }

    }

}

} // namespace Parser