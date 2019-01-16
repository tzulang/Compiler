#pragma once
#include "pch.h"


namespace compiler {


class NoMatchException : public std::exception
{
   public:
    virtual const char* what() const throw()
    {
        return "Parser No Match Found!";
    }

} noMatchException;


template <typename StringType>
struct MatchResult
{
    bool found;
    typename StringType::iterator start;
    typename StringType::iterator end;
};


template <typename StringType>
class BasicStringPredicate{
public:

    using iterator = typename StringType::iterator;
    using value_type = typename  StringType::value_type;
    using regex = std::basic_regex<value_type>;
    using match_results = std::match_results<const value_type*>;

    BasicStringPredicate() = delete;


    BasicStringPredicate(StringType const& pattern)
        : _pattern(pattern), _regex(pattern)
    {}


    MatchResult<StringType> operator()( iterator const& iter) const
    {

        match_results mres;
        const value_type *c = &*iter;
        bool found = std::regex_search(c, mres, _regex, std::regex_constants::match_continuous);
        if (found)
        {
                return {true, iter, iter + mres.length()};
        }
        return { false, iter, iter };


    }


    BasicStringPredicate& operator=(StringType const& s)
    {
            this->_pattern &= s;
            this->_regex = regex(_pattern);
            return *this;
    }


    BasicStringPredicate operator&(BasicStringPredicate const& other) const
    {
            return BasicStringPredicate(this->_pattern + other._pattern);
    }


    BasicStringPredicate& operator&=(BasicStringPredicate const& other)
    {
            this->_pattern &= other._pattern;
            this->_regex = regex(_pattern);
            return *this;
    }


    BasicStringPredicate operator|(BasicStringPredicate const& other) const
    {
            return BasicStringPredicate("[" + this->_pattern + "|" + other._pattern + "]");
    }


    BasicStringPredicate& operator|=(BasicStringPredicate const& other)
    {
            this->_pattern = "[" + this->_pattern + "|" + other._pattern + "]";
            this->_regex = regex(_pattern);
            return *this;
    }


    BasicStringPredicate maybe() const
    {
            return BasicStringPredicate("[" + this->_pattern + "]?");
    }



    const StringType& GetPattern() const
    {
            return _pattern;
    }





private:

    StringType _pattern;
    regex  _regex;
};


} //namespace compiler



template <typename StringType>
std::ostream & operator << (std::ostream &out, compiler::MatchResult<StringType> const& m)
{
    if (!m.found)
    {
        out <<"MatchResult_Error<No Match>";
    } else {

        out <<"MatchResult<"  ;
        for (auto it= m.start; it <m.end;it ++)
        {
            out <<*it;
        }
        out <<">";
    }
    return out;
}
