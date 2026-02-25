#include <gtest/gtest.h>
#include "SyntaxAnalysis.hpp"
#include <vector>

using namespace SLR;
using namespace SLR::Parser;

TEST(ParserTest, ValidExpression)
{
    std::vector<Token> Tokens = 
    {
        {TokenType::ID,   "a"},
        {TokenType::PLUS, "+"},
        {TokenType::ID,   "b"},
        {TokenType::END_OF_FILE, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SUCCESS);
}

TEST(ParserTest, Brackets)
{
    std::vector<Token> Tokens = 
    {
        {TokenType::L_BRACKET, "("},
        {TokenType::L_BRACKET, "("},
        {TokenType::ID, "a"},
        {TokenType::R_BRACKET, ")"},
        {TokenType::R_BRACKET, ")"},
        {TokenType::END_OF_FILE, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SUCCESS);
}

TEST(ParserAdvanced, OperatorPrecedence)
{
    std::vector<Token> Tokens =
    {
        {TokenType::ID, "a"}, 
        {TokenType::PLUS, "+"}, 
        {TokenType::ID, "b"}, 
        {TokenType::MULT, "*"}, 
        {TokenType::ID, "c"}, 
        {TokenType::END_OF_FILE, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SUCCESS);
}

TEST(ParserAdvanced, UnaryMinus)
{
    std::vector<Token> Tokens =
    {
        {TokenType::MINUS, "-"},
        {TokenType::ID, "a"}, 
        {TokenType::PLUS, "+"}, 
        {TokenType::ID, "b"}, 
        {TokenType::END_OF_FILE, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SUCCESS);
}


TEST(ParserTest, InvalidExpression)
{
    std::vector<Token> Tokens = 
    {
        {TokenType::PLUS, "+"},
        {TokenType::ID, "a"},
        {TokenType::END_OF_FILE, "$"}
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SYNTAX_ERROR);
}

TEST(ParserTest, MissingEOF)
{
    std::vector<Token> Tokens = 
    {
        {TokenType::ID, "a"},
        {TokenType::MULT, "*"},
        {TokenType::ID, "b"},
    };

    SyntaxAnalysis parser;

    EXPECT_EQ(parser.SLRParser(Tokens), Status::SYNTAX_ERROR);
}