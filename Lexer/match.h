#pragma once

namespace compiler
{

class NoMatchException : public std::exception
{
   public:
    virtual const char* what() const throw()
    {
        return "Parser No Match Found!";
    }

} noMatchException;


class AddMatchException : public std::exception
{
   public:
    virtual const char* what() const throw()
    {
        return "adding matches is only possible when the iterators are continuos and valid";
    }

} addMatchException;

template <typename ValueType>
class MatchResult
{

public:

    using iterator =  typename ValueType::iterator;


    MatchResult(bool found, iterator const& start, iterator const& end)
        : _found(found), _begin(start), _end(end)
    {}

    explicit operator bool() const
    {
        return _found;
    }


    inline  bool operator !() const
    {
        return (!this->operator bool());
    }

    MatchResult operator + (MatchResult<ValueType> const& other) const {

        if (this->end() != other.begin() || !*this || !other)
        {
            throw addMatchException;
        }

        return {true, this->begin(), other.end()};
    }

    MatchResult& operator += (MatchResult<ValueType> & other) const {

        if (this->end != other || !*this || !other)
        {
            throw addMatchException;
        }
        this->_end=  other._end ;
        return *this;
    }

    const iterator& begin() const { return _begin;}
    const iterator& end()   const { return _end;}

private:

    bool _found;
    iterator _begin;
    iterator _end;

};





}//namespace compiler



template <typename StringType>
std::ostream & operator << (std::ostream &out, compiler::MatchResult<StringType> const& m)
{
    if (!m)
    {
        out <<"MatchResult_Error<No Match>";
    } else {

        out <<"MatchResult<"  ;
        for (auto it= m.begin(); it <m.end();it ++)
        {
            out <<*it;
        }
        out <<">";
    }
    return out;
}
