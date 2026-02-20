#pragma once

#include <string>

enum TokenType
{
    TOKEN_EOF = 0,
    TOKEN_ID = 1,
    TOKEN_PLUS = 2,
    TOKEN_MULT = 3,
    UNKNOWN_TOKEN = 4
};

struct Token
{
    int TokenType;
    std::string attribute;
};