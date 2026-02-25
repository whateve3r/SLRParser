#pragma once

#include <string>

namespace SLR {

enum class TokenType
{
    END_OF_FILE =  0,
    
    ID          =  1,

    PLUS        =  2,
    MINUS       =  3,
    MULT        =  4,
    DIV         =  5,

    L_BRACKET   =  6,
    R_BRACKET   =  7,

    UNKNOWN     =  8
};

struct Token
{
    TokenType Type;
    std::string Attribute;
};

}