#include "testutils.h"
#include "Lexer/parsercombinatror.h"
#include "Lexer/match.h"
#include "MyLanguage/definitions.h"
#include <string_view>
#include <locale>


using namespace compiler;
using str = strType;



TEST(testStringParser, testpChar)
{
   auto pa= pChar<str>('a');
   str s1 = S("abcd");
   str s2 = S("bcd");

   assertFound<str>(pa,s1.begin(), S("a"), s2);
   assertNotFound<str>(pa ,s2.begin());


}


TEST(testStringParser, testConcat)
{
    auto pa= pChar<str>('a');
    auto pb= pChar<str>('b');
    auto pc= pChar<str>('c');

    auto pConcatAbc = pConcat(ParserList<str>{pa,pb,pc});
    std::vector<str> failed_cases= {S("bcdef"), S("acdef"), S("abdef")};
    str s = S("abcdef");
    str r = S("def");

    assertFound<str>(pConcatAbc, s.begin(), S("abc") , r);
    for ( auto& f: failed_cases)
    {
        assertNotFound<str>(pConcatAbc, f.begin());
    }

    auto pConcatA = pConcat(ParserList<str>{pa});
    assertFound<str>(pConcatA, s.begin(), s.substr(0,1) , s.substr(1));
    assertNotFound<str>(pConcatA ,failed_cases[0].begin());

    auto pConcatEmpty = pConcat(ParserList<str>{});
    assertFound<str>(pConcatEmpty, s.begin(), S("") ,  s);

    auto pDoubleA =pConcat<str>({pa,pa});
    auto pConcatSquare = pConcat<str>({pDoubleA,pDoubleA});
    str s4 = S("aaaaabcd");
    str s3 = S("aaabcd");
    assertFound<str>(pDoubleA, s4.begin(), S("aa") , S("aaabcd"));
    assertFound<str>(pConcatSquare, s4.begin(), S("aaaa") , S("abcd"));
    assertNotFound<str>(pConcatSquare ,s3.begin());

}


TEST(testStringParser, testOr)
{
    auto pa= pChar<str>('a');
    auto pb= pChar<str>('b');
    auto pc= pChar<str>('c');

    auto pOrAbc = pOneOf(ParserList<str>{pa,pb,pc});
    std::vector<str> cases= {S("abcd"), S("bbcd"), S("cbcd")};
    str f = S("fbcd");
    str r = S("bcd");

    for ( auto& s: cases)
    {
        str b=str(s.substr(0,1));
        assertFound<str>(pOrAbc, s.begin(),b , r);

    }
    assertNotFound<str>(pOrAbc ,f.begin());

    auto pOrA = pOneOf(ParserList<str>{pa});
    assertFound<str>(pOrA, cases[0].begin(), cases[0].substr(0,1) , r);
    assertNotFound<str>(pOrA ,f.begin());

    auto pOrEmpty = pOneOf(ParserList<str>{});
    assertFound<str>(pOrEmpty, cases[0].begin(), S("") , cases[0]);

    auto pAB = pConcat<str>({pa,pb});
    auto pLongOR = pOneOf<str>({pAB, pAB});
    str abab = S("ababababc");
    assertFound<str>(pLongOR, abab.begin(), S("ab") , S("abababc"));

}


TEST(testStringParser, testMaybe)
{
    auto pa= pChar<str>('a');
    auto pMaybeA = pMaybe(pa);
    std::vector<str> cases= {S("bcdef"),S("acdef"), S("abdef")};

    for ( auto& s: cases)
    {
        if (s[0] == 'a')
            assertFound<str>(pMaybeA, s.begin(), S("a") , s.substr(1));
        else
            assertFound<str>(pMaybeA, s.begin(), S("") ,  s);
    }
}


TEST(testStringParser, testAny)
{
    std::vector<str> cases= {S("bcdef"), S("acdef"), S("rbdef")};
    for ( auto& s: cases)
    {
        assertFound<str>(pAny<str>, s.begin(), s.substr(0,1) , s.substr(1));
    }
}


TEST(testStringParser, testMany)
{
    auto pa= pChar<str>('a');
    auto pManyA = pMany(pa);

    std::vector<str> cases= {S("cdef"), S("acdef"), S("aacdef"), S("aaacdef"),  S("aaaacdef")};
    str a=S("");
    for ( auto& s: cases)
    {
        assertFound<str>(pManyA , s.begin(), a , s.substr(a.size()));
        a+=S("a");
    }
}


TEST(testStringParser, testRepeat)
{
    auto pa= pChar<str>('a');

    std::vector<str> cases= {S("cdef"), S("acdef"), S("aacdef"), S("aaacdef"), S("aaaacdef")};
    str a = S("");
    for (size_t i =0 ; i < cases.size(); i ++)
    {
        for (size_t j =0 ; j < cases.size(); j ++)
        {
            auto pRepeatA = pRepeat<str>(pa,i);
            if (i <= j)
                assertFound<str>(pRepeatA , cases[j].begin(), a , cases[j].substr(i));
            else
                assertNotFound<str>(pRepeatA, cases[j].begin());
        }
        a+=S("a");
    }
}


TEST(testStringParser, testAtLeat)
{
    auto pa= pChar<str>('a');

    std::vector<str> cases= {S("cdef"), S("acdef"), S("aacdef"), S("aaacdef"), S("aaaacdef")};

    for (size_t i =0 ; i < cases.size(); i ++)
    {
        for (size_t j =0 ; j < cases.size(); j ++)
        {
            auto pAtLeastA = pAtLeast<str>(pa,i);
            if (i <= j){
                auto as=cases[j].substr(0,j);
                auto rest = cases[j].substr(j);
                assertFound<str>(pAtLeastA , cases[j].begin(), as , rest);
            }
            else
                assertNotFound<str>(pAtLeastA, cases[j].begin());
        }
    }

}


TEST(testStringParser, testRange)
{

    auto rangeAD = pRange<str>('a','d');
    std::vector<str> cases= {S("adef"), S("bdef"), S("cdef"), S("ddef")};
    str f = S("edef");

    for (str & s: cases)
        assertFound<str>(rangeAD, s.begin(), s.substr(0,1), S("def"));
    assertNotFound<str>(rangeAD, f.begin());
}


TEST(testStringParser, testWord)
{
    auto word = pWord(strType(S("abcd")));
    str s = S("abcd");
    str r = S("efg");
    str f = S("abcefg");

    assertFound<str>(word, (s+r).begin(), s, r);

}

TEST(testStringParser, testMatchMax)
{
    str s = S("abcdefg");
    ParserList<str> parsers;
    for (auto & c: s)
    {
        parsers.push_back(pChar<str>(c));
    }


    for (size_t i : Range<size_t>(0,parsers.size()))
    {
        ParserList<str> pack(parsers.begin(), parsers.begin() + i);
        auto pMax = pMatchMax(pack);
        assertFound(pMax, s.begin(), s.substr(0,i), s.substr(i));

    }
}

TEST_MAIN
