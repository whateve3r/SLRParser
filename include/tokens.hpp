#pragma once

#include <string>

enum TokenType
{
    TOKEN_EOF      =  0,
    
    TOKEN_ID       =  1,

    TOKEN_PLUS     =  2,
    TOKEN_MINUS    =  3,
    TOKEN_MULT     =  4,
    TOKEN_DIV      =  5,

    TOKEN_LBRACKET =  6,
    TOKEN_RBRACKET =  7,

    UNKNOWN_TOKEN  =  8
};

struct Token
{
    int TokenType;
    std::string attribute;
};