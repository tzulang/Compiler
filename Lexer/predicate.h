#pragma once
#include "pch.h"


namespace compiler {

class NoMatchException : public std::exception
{
   public:
    virtual const char* what() const throw() {
            return "Parser No Match Found!";
    }

} noMatchException;

template <typename StringType, typename TokenType>
struct MatchResult
{
        bool found;
        TokenType tokenType;
        typename StringType::iterator start;
        typename StringType::iterator end;
};


template <typename StringType, typename TokenType =StringType>
class BasicStringPredicate{
public:

    using Iterator = typename StringType::iterator;
    using CharType = typename  StringType::value_type;
    using Regex = std::basic_regex<CharType>;
    using RegexMatch = std::match_results<const CharType*>;

    BasicStringPredicate() = delete;


    BasicStringPredicate(StringType const& pattern, TokenType const& token)
        : _pattern(pattern), _regex(pattern),_token(token)
    {}


    MatchResult<StringType, TokenType > operator()(Iterator const& iterator) const
    {

        RegexMatch mres;
        const CharType *c = &*iterator;
        bool found = std::regex_search(c, mres, _regex, std::regex_constants::match_continuous);
        if (found)
        {
                return {true, _token, iterator, iterator + mres.length()};
        }
        return { false, _token, iterator, iterator };


    }


    BasicStringPredicate& operator=(StringType const& s)
    {
            this->_pattern &= s;
            this->_regex = Regex(_pattern);
            return *this;
    }


    BasicStringPredicate operator&(BasicStringPredicate const& other) const
    {
            return BasicStringPredicate(this->_pattern + other._pattern);
    }


    BasicStringPredicate& operator&=(BasicStringPredicate const& other)
    {
            this->_pattern &= other._pattern;
            this->_regex = Regex(_pattern);
            return *this;
    }


    BasicStringPredicate operator|(BasicStringPredicate const& other) const
    {
            return BasicStringPredicate("[" + this->_pattern + "|" + other._pattern + "]");
    }


    BasicStringPredicate& operator|=(BasicStringPredicate const& other)
    {
            this->_pattern = "[" + this->_pattern + "|" + other._pattern + "]";
            this->_regex = Regex(_pattern);
            return *this;
    }


    const StringType& GetPattern() const
    {
            return _pattern;
    }


    const TokenType& GetToken(){ return _token;}


private:

    StringType _pattern;
    TokenType _token;
    Regex  _regex;
};


} //namespace compiler



template <typename StringType, typename TokenType=StringType>
std::ostream & operator << (std::ostream &out, compiler::MatchResult<StringType,TokenType> const& m)
{

    if (!m.found)
    {
        out <<"MatchResult_Error<No Match>";
    } else {

        out <<"MatchResult<"  << m.tokenType << ", ";
        for (auto it= m.start; it <m.end;it ++)
        {
            out <<*it;
        }
        out <<">";
    }

    return out;
}
