#pragma once
#include "pch.h"
#include "match.h"

#include <tuple>


namespace compiler {


template <typename StringType>
class BasicStringPredicate
{
public:

    using iterator = typename StringType::iterator;
    using value_type = StringType;

    using string_value_type = typename  StringType::value_type;
    using regex = std::basic_regex<string_value_type>;
    using match_results = std::match_results<const string_value_type*>;

    BasicStringPredicate() = delete;


    BasicStringPredicate(StringType const& pattern)
        : _pattern(pattern), _regex(pattern)
    {}


    MatchResult<StringType> operator()( iterator const& iter) const
    {
        match_results mres;
        const string_value_type *c = &*iter;
        bool found = std::regex_search(c, mres, _regex, std::regex_constants::match_continuous);

        if (found)
        {
            return {true, iter, iter + mres.length()};
        }

        return {false, iter, iter};
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



//template <typename StringType>
//class BasicStringPredicate{
//public:

//    using iterator = typename StringType::iterator;
//    using value_type = typename  StringType::value_type;
//    using regex = std::basic_regex<value_type>;
//    using match_results = std::match_results<const value_type*>;

//    BasicStringPredicate() = delete;


//    BasicStringPredicate(StringType const& pattern)
//        : _pattern(pattern), _regex(pattern)
//    {}


//    MatchResult<StringType> operator()( iterator const& iter) const
//    {

//        match_results mres;
//        const value_type *c = &*iter;
//        bool found = std::regex_search(c, mres, _regex, std::regex_constants::match_continuous);
//        if (found)
//        {
//                return {true, iter, iter + mres.length()};
//        }
//        return { false, iter, iter };


//    }


//    BasicStringPredicate& operator=(StringType const& s)
//    {
//            this->_pattern &= s;
//            this->_regex = regex(_pattern);
//            return *this;
//    }


//    BasicStringPredicate operator&(BasicStringPredicate const& other) const
//    {
//            return BasicStringPredicate(this->_pattern + other._pattern);
//    }


//    BasicStringPredicate& operator&=(BasicStringPredicate const& other)
//    {
//            this->_pattern &= other._pattern;
//            this->_regex = regex(_pattern);
//            return *this;
//    }


//    BasicStringPredicate operator|(BasicStringPredicate const& other) const
//    {
//            return BasicStringPredicate("[" + this->_pattern + "|" + other._pattern + "]");
//    }


//    BasicStringPredicate& operator|=(BasicStringPredicate const& other)
//    {
//            this->_pattern = "[" + this->_pattern + "|" + other._pattern + "]";
//            this->_regex = regex(_pattern);
//            return *this;
//    }


//    BasicStringPredicate maybe() const
//    {
//            return BasicStringPredicate("[" + this->_pattern + "]?");
//    }



//    const StringType& GetPattern() const
//    {
//            return _pattern;
//    }





//private:

//    StringType _pattern;
//    regex  _regex;
//};


} //namespace compiler



