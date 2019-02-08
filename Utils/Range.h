#pragma once

#include <vector>
#include <iostream>

template<typename T>
class Range
{

public:

    Range(T const& begin, T const& end, size_t step=1)
        : _begin(begin), _end(end), _step(step)
    {}


    class iterator
    {
    public:
        iterator(Range<T> const& range, T const & t)
            : _range(range),_current(t)
        {


        }
    public:

        iterator operator++ (int)
        {
            auto prev = *this;
            this->_current+=_range._step ;
            return prev;
        }

        iterator& operator ++ ()
        {
            _current += _range._step;
            return *this;
        }

        inline bool operator == (iterator const& other) const {
            return _current == other._current;
        }

        inline bool operator != (iterator const& other) const {
            return _current != other._current;
        }

        inline bool operator < (iterator const& other) const{
            return _current < other._current;
        }

        inline bool operator > (iterator const& other) const{
            return _current > other._current;
        }

        inline bool operator <= (iterator const& other) const{
            return _current < _range.other._current;
        }

        inline bool operator >= (iterator const& other) const{
            return _current >= _range.other._current;
        }

        inline T& operator * () {
            return _current;
        }

        inline T& operator ->(){
            return _current;
        }

    private:
        T _current;
        const Range<T> & _range;
    };


    iterator begin() { return iterator(*this, _begin);}
    iterator end()   { return iterator(*this, _end);}

    size_t size() {return _end-_begin;}

    std::vector<T> as_vector()
    {
        std::vector<T> res;
        res.reserve(this->size());
        for (auto& i: *this)
        {
            res.push_back(i);
        }

        return res;
    }

private:

    T _begin, _end;
    size_t _step;

};
