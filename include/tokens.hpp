#pragma once

#include <string>

namespace SLR {

enum class TokenType
{    
    ID          =  0,

    PLUS        =  1,
    MINUS       =  2,
    MULT        =  3,
    DIV         =  4,

    L_BRACKET   =  5,
    R_BRACKET   =  6,

    END_OF_FILE =  7,


    UNKNOWN     =  8
};

struct Token
{
    TokenType Type;
    std::string Attribute;
};

}