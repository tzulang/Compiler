#pragma once

#include "match.h"
#include "pch.h"
//#include <optional>

namespace compiler
{

template<typename StringType>
using Parser = std::function<MatchResult<StringType>(typename StringType::iterator const&)>;

template<typename StringType>
using ParserList =std::vector<Parser<StringType>>;



template <typename StringType>
Parser<StringType> pChar(
        typename StringType::value_type const& c)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        if (*it == c)
            return MatchResult<StringType>(true, it, it + 1);
        else
            return MatchResult<StringType>(false, it, it);
    };

    return p;
}


template <typename StringType>
Parser<StringType> pAnd(ParserList<StringType> const& parsers)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        MatchResult<StringType> res={true , it , it};
        auto crntIt = it;
        for (Parser<StringType> const& parser : parsers)
        {
            MatchResult<StringType> match = parser(crntIt);
            if (!match)
                   return MatchResult<StringType>({false, it , it});
            res= res + match;
            crntIt++;
        }

        return res;
    };

    return p;
}


template <typename StringType>
Parser<StringType> pOr(ParserList<StringType> const& parsers)
{
    auto p = [=](typename StringType::iterator const& it)
    {

        auto crntIt = it;
        for (Parser<StringType> const& parser : parsers)
        {
            auto match = parser(crntIt);
            if (match)
                return match;
        }

        return MatchResult<StringType>{false, it , it};
    };

    return p;
}


template <typename StringType>
Parser<StringType> pMaybe(Parser<StringType> const& parser)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        auto match = parser(it);
        if (match)
            return match;
        else
            return MatchResult<StringType>{true, it , it};
    };
    return p;
}

template <typename StringType>
MatchResult<StringType> pAny(typename StringType::iterator const& it)
{
    return MatchResult<StringType>{true, it , it+1};
}


template <typename StringType>
Parser<StringType> pMany(Parser<StringType> const& parser)
{

    auto p = [=](typename StringType::iterator const& it)
    {
        MatchResult<StringType> res={true, it , it};
        while (auto match = parser(it))
        {
            if (match)
                res+= match;
        }
    };
    return p;
}

template <typename StringType>
Parser<StringType> pOneOrMore(Parser<StringType> const& parser)
{
    return pAnd(parser, pMany);
}

template <typename StringType>
Parser<StringType> pRepeat(Parser<StringType> const& parser, size_t n)
{
    if (n ==0);
        return MatchResult<StringType>{true, it , it};
    Parser res=parser;
    for (size_t; i<n; i++)
        res =pAnd(res, pMany);
    return res;
}



}//namespace compiler
