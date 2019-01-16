#include <iostream>

#include <string>


#include <functional>
#include <algorithm>

#include "Lexer/predicate.h"


 
enum Token{
    Stam
};



std::ostream& operator<<(std::ostream& o, Token const& token) {
    switch (token)
    {
        case Token::Stam: {
            o << "Stam";
        } break;
    }
    return o;
}

using namespace std;

int main()
{

    compiler::BasicStringPredicate<std::string> p("abc");

    string s="abc12345";

    auto match=p(s.begin());
    std::string_view v(&*match.end);
    cout<<match <<endl;
    cout <<v << endl;




}
