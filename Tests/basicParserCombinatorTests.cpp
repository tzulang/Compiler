#include "testutils.h"
#include "MyLanguage/basicparsercombinators.h"
#include "Lexer/match.h"
#include "MyLanguage/definitions.h"
#include <string_view>
#include <locale>

using namespace compiler;
using namespace Lexer;

using str = strType;



TEST(testStringParser, testLower)
{
   auto lower = Range<str::value_type> ('a', 'z'+1);
   str rest =S("1234");

   for (auto const& c : lower)
   {
       str s = str(1, c) + rest;
       assertFound<str>(pLowerCase, s.begin(), str(1, c), rest);
   }
}


TEST(testStringParser, testUpper)
{
   auto upper = Range<str::value_type> ('A', 'Z'+1);
   str rest =S("1234");

   for (auto const& c : upper)
   {
       str s = str(1, c) + rest;
       assertFound<str>(pUpperCase, s.begin(), str(1, c), rest);
   }
}


TEST(testStringParser, testDigit)
{
   auto upper = Range<str::value_type> ('0', '9'+1);
   str rest =S("abcd");

   for (auto const& c : upper)
   {
       str s = str(1, c) + rest;
       assertFound<str>(pDigit, s.begin(), str(1, c), rest);
   }
}

TEST_MAIN
