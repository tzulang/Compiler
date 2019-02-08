#include "testutils.h"
#include "MyLanguage/parser.h"
#include "Lexer/token.h"

using namespace compiler;
using str = strType;


TEST(LexerText,testIntegers)
{

    std::vector<str> integerNumbers = {S("123"), S("0") ,S("1") , S("312312")};
    for (str & nStr : integerNumbers)
    {
        assertFound<str>(Lexer::pInteger, nStr.begin(), nStr, S("") );
    }
}


TEST(LexerText,testFloats)
{

    std::vector<str> floatNumbers = {S("123.45"), S("0.0") ,S(".1") , S("312.312")};
    for (str & nStr : floatNumbers)
    {
        assertFound<str>(Lexer::pFloat, nStr.begin(), nStr, S("") );
    }
}


TEST(LexerText,testReal)
{
    std::vector<str> realNumbers = {
                                     S("123.45"), S("0.0") ,S(".1") , S("312.312"),
                                     S("123"), S("0") ,S("1") , S("312312")
                                    };

    for (str & nStr : realNumbers)
    {
        assertFound<str>(Lexer::pReal, nStr.begin(), nStr, S("") );
    }
}


TEST(LexerText, TokenizerTest)
{
    enum tokenType { Integer, Float, RealNumber };
    using TestTokeinzer= Tokenizer<tokenType, Parser<strType>, strType>;

    TestTokeinzer tInteger(Integer, Lexer::pInteger);
    std::vector<str> integerNumbers = {S("123"), S("0") ,S("1") , S("312312")};
    for (str & nStr : integerNumbers)
    {

        assertFound<tokenType, strType>(tInteger, nStr.begin(), nStr, S("") );
//        tInteger(nStr.begin());
    }


}


TEST_MAIN
