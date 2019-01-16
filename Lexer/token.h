#pragma once
#include "predicate.h"

template<typedef TokenType,typename Predicate>
class Token
{

public:

    Token(TokenType const& token, Predicate const& predicate)
        :tokenType(token), Predicate(predicate)
    {}

    const predicate& getPredicate() const { return predicate;}
private:
    const TokenType tokenType;
    const Predicate predicate;

}
