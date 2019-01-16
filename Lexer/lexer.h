#pragma onces

#include "predicate.h"
#include "pch.h"

namespace compiler {


template <typename StringType, typename TokenType>
class Lexer {

private:

    using Predicate = BasicStringPredicate<StringType, TokenType>;
    std::vector<Predicate> _predicates;

public:

    Lexer() = default;


    void add(TokenType const& tokenType, StringType const& pattern)
    {
        this->_predicates.emplace( pattern, tokenType);

    }


    void add(BasicStringPredicate<StringType> const& predicate)
    {
        this->_predicates.emplace(predicate);
    }


    auto nextToken(typename StringType::iterator const& begin)
    {
        for (auto const& predicate : _predicates)
        {
            auto match = predicate(begin);
            if (match.found())
            {
                return match.token;
            }
        }
        throw noMatchException;
    }


};

} //namespace compiler
