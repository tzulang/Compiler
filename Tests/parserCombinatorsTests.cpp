#include "testutils.h"
#include "Lexer/parsercombinatror.h"
#include "Lexer/match.h"

#include <string_view>
#include <locale>

using namespace compiler;

template <typename StringType>
class ParserStringCombinator : public ::testing::Test
{
public:

   using iterator = typename  StringType::iterator;

    auto matchToStringView(MatchResult<StringType> const& m)
    {
        return std::basic_string_view(&*m.begin(), m.size());
    }

    auto restToStringView(MatchResult<StringType> const& m)
    {
        return std::basic_string_view(&*m.end());
    }

    void assertFound(Parser<StringType> const& parser,iterator const& begin, StringType const& found, StringType const& rest)
    {
        auto match = parser(begin);
        ASSERT_TRUE(match);
        ASSERT_EQ(matchToStringView(match), found);
        ASSERT_EQ(restToStringView(match) ,(rest));
    }

    void assertNotFound(Parser<StringType> const& parser,iterator const& begin)
    {
        auto noMatch =parser(begin);
        ASSERT_FALSE(noMatch);
        ASSERT_EQ(matchToStringView(noMatch), "");
        ASSERT_EQ(restToStringView(noMatch), std::basic_string_view(&*begin));
    }

};

using str = std::string;
using testStringParser=ParserStringCombinator<str>;
//TODO: test on other encoding


TEST_F(testStringParser, testpChar)
{
   auto pa= pChar<str>('a');
   str s1 = "abcd";
   str s2 = "bcd";

   assertFound(pa,s1.begin(),"a",s2);
   assertNotFound(pa ,s2.begin());


}


TEST_F(testStringParser, testAnd)
{
    auto pa= pChar<str>('a');
    auto pb= pChar<str>('b');
    auto pc= pChar<str>('c');

    auto paAndAbc = pAnd(ParserList<str>{pa,pb,pc});
    std::vector<str> failed_cases= {"bcdef","acdef", "abdef"};
    str s = "abcdef";
    str r = "def";

    assertFound(paAndAbc, s.begin(), "abc" , r);
    for ( auto& f: failed_cases)
    {
        assertNotFound(paAndAbc, f.begin());
    }

    auto pAndA = pAnd(ParserList<str>{pa});
    assertFound(pAndA, s.begin(), s.substr(0,1) , s.substr(1));
    assertNotFound(pAndA ,failed_cases[0].begin());

    auto pAndEmpty = pAnd(ParserList<str>{});
    assertFound(pAndEmpty, s.begin(), "" ,  s);

    auto pDoubleA =pAnd<str>({pa,pa});
    auto pAndSquare = pAnd<str>({pDoubleA,pDoubleA});
    str s4="aaaaabcd";
    str s3 ="aaabcd";
    assertFound(pDoubleA, s4.begin(), "aa" , "aaabcd");
    assertFound(pAndSquare, s4.begin(), "aaaa" , "abcd");
    assertNotFound(pAndSquare ,s3.begin());

}


TEST_F(testStringParser, testOr)
{
    auto pa= pChar<str>('a');
    auto pb= pChar<str>('b');
    auto pc= pChar<str>('c');

    auto pOrAbc = pOr(ParserList<str>{pa,pb,pc});
    std::vector<str> cases= {"abcd", "bbcd", "cbcd"};
    str f = "fbcd";
    str r = "bcd";

    for ( auto& s: cases)
    {
        str b=str(s.substr(0,1));
        assertFound(pOrAbc, s.begin(),b , r);

    }
    assertNotFound(pOrAbc ,f.begin());

    auto pOrA = pOr(ParserList<str>{pa});
    assertFound(pOrA, cases[0].begin(), cases[0].substr(0,1) , r);
    assertNotFound(pOrA ,f.begin());

    auto pOrEmpty = pOr(ParserList<str>{});
    assertFound(pOrEmpty, cases[0].begin(), "" , cases[0]);

    auto pAB = pAnd<str>({pa,pb});
    auto pLongOR = pOr<str>({pAB, pAB});
    str abab = "ababababc";
    assertFound(pLongOR, abab.begin(), "ab" , "abababc");

}


TEST_F(testStringParser, testMaybe)
{
    auto pa= pChar<str>('a');
    auto pMaybeA = pMaybe(pa);
    std::vector<str> cases= {"bcdef","acdef", "abdef"};

    for ( auto& s: cases)
    {
        if (s[0] == 'a')
            assertFound(pMaybeA, s.begin(), "a" , s.substr(1));
        else
            assertFound(pMaybeA, s.begin(), "" ,  s);
    }
}


TEST_F(testStringParser, testAny)
{
    std::vector<str> cases= {"bcdef","acdef", "rbdef"};
    for ( auto& s: cases)
    {
        assertFound(pAny<str>, s.begin(), s.substr(0,1) , s.substr(1));
    }
}


TEST_F(testStringParser, testMany)
{
    auto pa= pChar<str>('a');
    auto pManyA = pMany(pa);

    std::vector<str> cases= {"cdef","acdef", "aacdef", "aaacdef",  "aaaacdef"};
    str a="";
    for ( auto& s: cases)
    {
        assertFound(pManyA , s.begin(), a , s.substr(a.size()));
        a+="a";
    }
}


TEST_F(testStringParser, testRepeat)
{
    auto pa= pChar<str>('a');

    std::vector<str> cases= {"cdef","acdef", "aacdef", "aaacdef",  "aaaacdef"};
    str a = "";
    for (int i =0 ; i < cases.size(); i ++)
    {
        for (int j =0 ; j < cases.size(); j ++)
        {
            auto pRepeatA = pRepeat<str>(pa,i);
            if (i <= j)
                assertFound(pRepeatA , cases[j].begin(), a , cases[j].substr(i));
            else
                assertNotFound(pRepeatA, cases[j].begin());
        }
        a+="a";
    }
}


TEST_F(testStringParser, testAtLeat)
{
    auto pa= pChar<str>('a');

    std::vector<str> cases= {"cdef","acdef", "aacdef", "aaacdef",  "aaaacdef"};

    for (int i =0 ; i < cases.size(); i ++)
    {
        for (int j =0 ; j < cases.size(); j ++)
        {
            auto pAtLeastA = pAtLeast<str>(pa,i);
            if (i <= j){
                auto as=cases[j].substr(0,j);
                auto rest = cases[j].substr(j);
                assertFound(pAtLeastA , cases[j].begin(), as , rest);
            }
            else
                assertNotFound(pAtLeastA, cases[j].begin());
        }
    }

}


TEST_MAIN
