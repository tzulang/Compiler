#include <iostream>

#include <string>


#include <functional>
#include <algorithm>
#include <optional>

#include "Lexer/predicate.h"
#include "Lexer/token.h"
#include "Lexer/parsercombinatror.h"
#include "Utils/Range.h"
#include "MyLanguage/definitions.h"
#include <locale>


enum class MyToken{
    Stam,

    none_type
};



std::ostream& operator<<(std::ostream& o, MyToken const& token) {
    switch (token)
    {
        case MyToken::Stam: {
            o << "Stam";
        } break;

        default: {
            o <<"None";
        } break;
    }
    return o;
}

template<typename StringType>
StringType str(std::string const& s)
{
    return s;
}

template< >
std::wstring str(std::string const& s)
{
    return std::wstring(s.begin(), s.end());
}



using namespace std;
using namespace compiler;


//#define WIDEN2(x) L ## x
//#define S(x) WIDEN2(x)
//#define S(x) (x)

int main(int argc, char **argv)
{
    using namespace std::string_literals;

    char a='z';
    a++;
    Range<char> low('a',char('z'+1));
    auto lowVec = low.as_vector();

//    wstring s=S("asdasdasd") ;
//    wchar_t c= S('s');

//    wcout << c;

    std::u32string  s32= U"we";

//    Range srange(s.begin(), s.end());
//    for (auto c :low)
//    {
//        wcout << c << ", ";
//    }
//    cout << "d "<<Q(hello) << " " <<S(hello) <<endl;
//   std::string s= "aaaaabcdef";
//   auto pa=pChar<string>('a');
//   auto pr= pRepeat (pa, 2);
//   auto match= pr(s.begin());

//   auto match2 =pMany(pa)(match.end());

//   cout <<match <<'\n';
//   cout <<match2 <<'\n';;
//   auto pt = pConcat<string>({pa, pa});
//   auto ptt =pConcat<string>({pt,pt});
//   auto match3= ptt(s.begin());
//   cout <<match3 <<'\n';
//   cout<<"\n";


//    using namespace compiler;
//    auto  pA= pChar<std::string>('A');
//    auto  pB= pChar<std::string>('B');

//    auto pAB = pOr<std::string>({pA,pB});
//    string s= "BACD";
//    auto match = pAB(s.begin());
//    cout << match << endl;
//    cout <<string_view(&*match.begin(), match.end()-match.begin()  ) <<endl;
//    cout <<string_view(&*match.end()) <<endl;

//    cout <<endl;

//    Range<int> r(1,10);


//    auto v =r.as_vector();

//    for (auto i: v)
//    {
//        cout<< i << ", ";
//    }
    //    std::string b = (match) ? "true": "false";
    //    cout<< b <<endl;
    //    cout << v << endl;
//    using Predicate = compiler::BasicStringPredicate<std::string>;
//    Predicate p("abc");

//    optional<std::string>  opts;

//    cout << opts.value_or("no");

//    cout << endl;

//    compiler::Token<MyToken, Predicate> stamToken(MyToken::Stam, p);

//    compiler::Token< std::string, Predicate> stamToken("Stam", p);

//    compiler::BasicStringPredicate<std::string>::iterator it;

//    string s="abc12345";

//    it =s.begin();
//    auto match=p(it);


//    std::string_view v(&*match.end()  );
//    cout<< match <<endl;
//    std::string b = (match) ? "true": "false";
//    cout<< b <<endl;
//    cout << v << endl;

//    cout << stamToken(s.begin());



}
