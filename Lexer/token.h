#pragma once

#include "match.h"
#include "parsercombinatror.h"



namespace compiler
{

template<typename TokenType, typename ValueType>
struct Token
{
   MatchResult<ValueType> match;
   TokenType type;
};

template<typename TokenType, typename Predicate, typename PredicateValue>
class Tokenizer
{

public:

    Tokenizer(TokenType const& token, Predicate const& p)
        : _token(token),_predicate(p)
    { }


    auto operator() (typename PredicateValue::iterator const& it) const
    {
        MatchResult<PredicateValue> match = _predicate(it);
        return Token<TokenType, PredicateValue>{match, _token};
    }

private:

    TokenType _token;
    Predicate _predicate;
};

}//namespace compiler

