#include <iostream>

#include <string>


#include <functional>
#include <algorithm>

#include "Lexer/predicate.h"


template <typename T>
class Predicae
{
public:


private:

};




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

    compiler::BasicStringPredicate<std::string,Token> p("abc",Stam);

    string s="abc12345";


    auto match=p(s.begin());
    std::string_view v(&*match.end);
    cout<<match <<endl;
    cout <<v << endl;




}
