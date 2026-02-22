#include <gtest/gtest.h>
#include "LexicalAnalysis.hpp"

using namespace SLR;
using namespace SLR::Lexer;

TEST(LexerTest, RecognizesBasicTokens)
{
    std::string input = "x + 42";
    LexicalAnalysis lexer(input);

    ASSERT_EQ(lexer.getStatus(), Status::Success);
    const auto& tokens = lexer.getTokens();

    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].TokenType, TOKEN_ID);
    EXPECT_EQ(tokens[0].attribute, "x");
    EXPECT_EQ(tokens[2].TokenType, TOKEN_ID);
    EXPECT_EQ(tokens[2].attribute, "42");
    EXPECT_EQ(tokens[3].attribute, "$");
}

TEST(LexerTest, HandlesUnknownSymbol)
{
    std::string input = "a # b"; 
    LexicalAnalysis lexer(input);

    EXPECT_EQ(lexer.getStatus(), Status::Lexical_Error);
}