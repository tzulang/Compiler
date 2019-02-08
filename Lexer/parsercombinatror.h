#pragma once

#include "match.h"
#include "pch.h"
#include "Utils/Range.h"


namespace compiler
{


template<typename StringType>
using Parser = std::function<MatchResult<StringType>(typename StringType::iterator const&)>;


template<typename StringType>
using ParserList =std::vector<Parser<StringType>>;


template <typename StringType>
inline MatchResult<StringType> pBlank(typename StringType::iterator const& it) {
    return MatchResult<StringType>(true, it, it);
}


template <typename StringType>
inline  MatchResult<StringType> pTrue(typename StringType::iterator const& it) {
    return MatchResult<StringType>(true, it, it+1);
}


template <typename StringType>
inline MatchResult<StringType>  pFalse(typename StringType::iterator const& it) {
    return MatchResult<StringType>(false, it, it);
}


template <typename StringType>
inline Parser<StringType> pChar(typename StringType::value_type const& c)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        if (*it == c)
            return pTrue<StringType>(it);
        else
            return pFalse<StringType>(it);
    };

    return p;
}


template <typename StringType>
inline Parser<StringType> pPredicate( std::function<bool(typename StringType::value_type const&)> const& cp)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        if (cp(*it))
            return pTrue<StringType>(it);
        else
            return pFalse<StringType>(it);
    };

    return p;
}


template <typename StringType>
inline Parser<StringType> pConcat(ParserList<StringType> const& parsers)
{

    if (!parsers.size()) return pBlank<StringType>;

    auto p = [=](typename StringType::iterator const& it)
    {
        MatchResult<StringType> res=pBlank<StringType>(it);
        auto crntIt = it;
        for (Parser<StringType> const& parser : parsers)
        {
            MatchResult<StringType> match = parser(crntIt);
            if (!match)
                   return pFalse<StringType>(it);
            res= res + match;
            crntIt+= match.size();
        }

        return res;
    };

    return p;
}


template <typename StringType>
inline Parser<StringType> pOneOf(ParserList<StringType> const& parsers)
{

    if (!parsers.size()) return pBlank<StringType>;

    auto p = [=](typename StringType::iterator const& it)
    {

        auto crntIt = it;
        for (Parser<StringType> const& parser : parsers)
        {
            auto match = parser(crntIt);
            if (match)
                return match;
        }

        return pFalse<StringType>(it);
    };

    return p;
}


template <typename StringType>
inline Parser<StringType> pRange(
        typename StringType::value_type const& begin,
        typename StringType::value_type const& end)
{
    auto pastEnd =end ;
    pastEnd++;
    Range<typename StringType::value_type> range(begin, pastEnd);
    ParserList<StringType> parsers;
    parsers.reserve(range.size());
    for (auto const& c : range)
    {
        parsers.push_back(pChar<StringType>(c));
    }

    return pOneOf<StringType>(parsers);
}


template <typename StringType>
inline Parser<StringType> pMaybe(Parser<StringType> const& parser)
{
    auto p = [=](typename StringType::iterator const& it)
    {
        auto match = parser(it);
        if (match)
            return match;
        else
            return pBlank<StringType>(it);
    };
    return p;
}


template <typename StringType>
inline MatchResult<StringType> pAny(typename StringType::iterator const& it)
{
    return pTrue<StringType>(it);
}


template <typename StringType>
Parser<StringType> pMany(Parser<StringType> const& parser)
{

    auto p = [=](typename StringType::iterator const& it)
    {
        MatchResult<StringType> res={true, it , it};
        auto current =it;
        while (auto match = parser(current++))
        {
            if (match)
                res+= match;
        }

        return res;
    };
    return p;
}


template <typename StringType>
inline Parser<StringType> pRepeat(Parser<StringType> const& parser, size_t n)
{

    if (n ==0) return pBlank<StringType>;

    ParserList<StringType> res;
    res.reserve(n);
    for (size_t i=0; i<n; i++)
        res.push_back(parser);
    return pConcat(res);

}


template <typename StringType>
inline Parser<StringType> pAtLeast(Parser<StringType> const& parser, size_t n)
{
    return pConcat<StringType>({pRepeat<StringType>(parser, n), pMany<StringType>(parser)});
}


template <typename StringType>
inline Parser<StringType> pOneOrMore(Parser<StringType> const& parser)
{
    return pAtLeast(parser, 1);
}


template <typename StringType>
inline Parser<StringType> pWord(StringType const& word)
{

    ParserList<StringType> parsers;
    parsers.reserve(word.size());
    for (const auto& c : word )
    {
        parsers.push_back(pChar<StringType>(c));
    }

    return pConcat<StringType>(parsers);
}

template <typename StringType>
inline Parser<StringType> pMatchMax(ParserList<StringType> const& parsers)
{
    if (parsers.empty())
    {
        return pBlank<StringType>;
    }

    auto p = [=](typename StringType::iterator const& it)
    {
        auto parserItr = parsers.begin();
        auto match = (*parserItr)(it);
        if (!match)
        {
            return pFalse<StringType>(it);
        }


        for (parserItr++; parserItr != parsers.end(); parserItr++)
        {
            auto nextMatch = (*parserItr)(match.end());
            if (!nextMatch)
                return match;
            else
                match+= nextMatch;
        }

        return match;
    };

    return p;
}

}//namespace compiler
