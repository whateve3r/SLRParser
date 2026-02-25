#include <gtest/gtest.h>
#include "LexicalAnalysis.hpp"

using namespace SLR;
using namespace SLR::Lexer;

TEST(LexerTest, RecognizesBasicTokens)
{
    std::string input = "x + 42";
    LexicalAnalysis lexer(input);

    ASSERT_EQ(lexer.GetStatus(), Status::SUCCESS);
    const auto& tokens = lexer.GetTokens();

    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].Type, TokenType::ID);
    EXPECT_EQ(tokens[0].Attribute, "x");
    EXPECT_EQ(tokens[2].Type, TokenType::ID);
    EXPECT_EQ(tokens[2].Attribute, "42");
    EXPECT_EQ(tokens[3].Type, TokenType::END_OF_FILE);
    EXPECT_EQ(tokens[3].Attribute, "$");
}

TEST(LexerTest, HandlesUnknownSymbol)
{
    std::string input = "a # b"; 
    LexicalAnalysis lexer(input);

    EXPECT_EQ(lexer.GetStatus(), Status::LEXICAL_ERROR);
}
