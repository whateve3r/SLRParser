#include <gtest/gtest.h>
#include "SyntaxAnalysis.hpp"
#include <vector>

using namespace SLR;
using namespace SLR::Parser;

TEST(ParserTest, ValidExpression)
{
    std::vector<Token> Tokens = 
    {
        {TOKEN_ID, "a"},
        {TOKEN_PLUS, "+"},
        {TOKEN_ID, "b"},
        {0, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Success);
}

TEST(ParserTest, Brackets)
{
    std::vector<Token> Tokens = 
    {
        {TOKEN_LBRACKET, "("},
        {TOKEN_LBRACKET, "("},
        {TOKEN_ID, "a"},
        {TOKEN_RBRACKET, ")"},
        {TOKEN_RBRACKET, ")"},
        {0, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Success);
}

TEST(ParserAdvanced, OperatorPrecedence)
{
    std::vector<Token> Tokens =
    {
        {TOKEN_ID, "a"}, 
        {TOKEN_PLUS, "+"}, 
        {TOKEN_ID, "b"}, 
        {TOKEN_MULT, "*"}, 
        {TOKEN_ID, "c"}, 
        {0, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Success);
}

TEST(ParserAdvanced, UnaryMinus)
{
    std::vector<Token> Tokens =
    {
        {TOKEN_MINUS, "-"},
        {TOKEN_ID, "a"}, 
        {TOKEN_PLUS, "+"}, 
        {TOKEN_ID, "b"}, 
        {0, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Success);
}


TEST(ParserTest, InvalidExpression)
{
    std::vector<Token> Tokens = 
    {
        {TOKEN_PLUS, "+"},
        {TOKEN_ID, "a"},
        {0, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Syntax_Error);
}

TEST(ParserTest, MissingEOF)
{
    std::vector<Token> Tokens = 
    {
        {TOKEN_ID, "a"},
        {TOKEN_MULT, "*"},
        {TOKEN_ID, "b"},
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::Syntax_Error);
}