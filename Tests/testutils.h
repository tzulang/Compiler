#pragma once

#include <gtest/gtest.h>
#include "Lexer/match.h"
#include "Lexer/parsercombinatror.h"
#include "Lexer/token.h"
#include "MyLanguage/definitions.h"


#define TEST_MAIN  \
int main(int argc, char **argv) {\
    ::testing::InitGoogleTest(&argc, argv);\
    return RUN_ALL_TESTS();\
}






template <typename StringType>
auto matchToStringView(compiler::MatchResult<StringType> const& m)
{
    return std::basic_string_view(&*m.begin(), m.size());
}


template <typename StringType>
auto restToStringView(compiler::MatchResult<StringType> const& m)
{
    return std::basic_string_view(&*m.end());
}

template <typename StringType>
void assertFound(compiler::Parser<StringType> const& parser,typename  StringType::iterator const& begin, StringType const& found, StringType const& rest)
{
    auto match = parser(begin);
    ASSERT_TRUE(match);
    ASSERT_EQ(matchToStringView(match), found);
    ASSERT_EQ(restToStringView(match) ,(rest));
}

template <typename StringType>
void assertNotFound(compiler::Parser<StringType> const& parser,typename  StringType::iterator const& begin)
{
    auto noMatch =parser(begin);
    ASSERT_FALSE(noMatch);
    ASSERT_EQ(matchToStringView(noMatch), S(""));
    ASSERT_EQ(restToStringView(noMatch), std::basic_string_view(&*begin));
}


template <typename TokenType, typename StringType>
void assertFound(compiler::Tokenizer<TokenType, compiler::Parser<StringType>, StringType> const& tokenizer
                 ,typename  StringType::iterator const& begin, StringType const& found, StringType const& rest)
{

    auto token = tokenizer(begin);
    ASSERT_TRUE(token.match);
//    ASSERT_EQ(matchToStringView(match), found);
//    ASSERT_EQ(restToStringView(match) ,(rest));
}
