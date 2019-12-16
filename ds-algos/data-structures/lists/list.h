#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <math.h>
#include <new>
#include <cassert>      // assert
#include <cstddef>      // ptrdiff_t
//#include <iterator>     // iterator
#include <type_traits>  // remove_cv
#include <utility>      // swap


template< class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class ForwardIterator : public std::iterator<std::forward_iterator_tag, UnqualifiedType, std::ptrdiff_t, Type*, Type&>
{   
    //using value_type = T;
    typedef std::forward_iterator_tag iterator_category;
    typedef Type value_type;
    typedef std::ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;


    node<UnqualifiedType>* itr;

    explicit ForwardIterator(node<UnqualifiedType>* nd) 
        : itr(nd) 
    { 
    }

public:

    ForwardIterator()   // Default construct gives end.
        : itr(nullptr) 
    { 
    }

    void swap(ForwardIterator& other) noexcept
    {
        using std::swap;
        swap(itr, other.iter);
    }

    ForwardIterator& operator++ () // Pre-increment
    {
        assert(itr != nullptr && "Out-of-bounds iterator increment!");
        itr = itr->next;
        return *this;
    }

    ForwardIterator operator++ (int) // Post-increment
    {
        assert(itr != nullptr && "Out-of-bounds iterator increment!");
        ForwardIterator tmp(*this);
        itr = itr->next;
        return tmp; 
    }

    // two-way comparison: v.begin() == v.cbegin() and vice versa
    template<class OtherType>
    bool operator == (const ForwardIterator<OtherType>& rhs) const
    {
        return itr == rhs.itr;
    }

    template<class OtherType>
    bool operator != (const ForwardIterator<OtherType>& rhs) const
    {
        return itr != rhs.itr;
    }

    Type& operator* () const
    {
        assert(itr != nullptr && "Invalid iterator dereference!");
        return itr->data;
    }

    Type& operator-> () const
    {
        assert(itr != nullptr && "Invalid iterator dereference!");
        return itr->data;
    }

    // One way conversion: iterator -> const_iterator
    operator ForwardIterator<const Type>() const
    {
        return ForwardIterator<const Type>(itr);
    }
};

// `iterator` and `const_iterator` used by your class:
//typedef ForwardIterator<T> iterator;
//typedef ForwardIterator<const T> const_iterator;

template< class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class Iterator
{
public:
    using value_type = UnqualifiedType;
    using pointer    = UnqualifiedType*;
    using reference  = UnqualifiedType&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Iterator():                    v(nullptr), i(0) {}   
    Iterator(Vector<Type>* v, int i): v(v),       i(i) {}
    // Default Copy/Move Are Fine.
    Iterator(Iterator &it)  = default;
    Iterator(Iterator &&it) = default;
    // Default Destructor fine.
    ~Iterator() = default;

    reference       operator*()             {return (*v)[i];}
    const reference operator*()       const {return (*v)[i];}
    pointer         operator->()            {return &((*v)[i]);}
    const pointer   operator->()      const {return &((*v)[i]);}
    reference       operator[](int m)       {return (*v)[i + m];}
    const reference operator[](int m) const {return (*v)[i + m];}


    Iterator& operator++()       {++i;return *this;}
    Iterator& operator--()       {--i;return *this;}
    Iterator  operator++(int)    {Iterator r(*this);++i;return r;}
    Iterator  operator--(int)    {Iterator r(*this);--i;return r;}

    Iterator& operator+=(int n)  {i += n;return *this;}
    Iterator& operator-=(int n)  {i -= n;return *this;}

    Iterator operator+(int n)   const {Iterator r(*this);return r += n;}
    Iterator operator-(int n)   const {Iterator r(*this);return r -= n;}

    difference_type operator-(Iterator const& r) const {return i - r.i;}

    // Note: comparing iterator from different containers
    //       is undefined behavior so we don't need to check
    //       if they are the same container.
    bool operator<(Iterator const& r)  const {return i <  r.i;}
    bool operator<=(Iterator const& r) const {return i <= r.i;}
    bool operator>(Iterator const& r)  const {return i >  r.i;}
    bool operator>=(Iterator const& r) const {return i >= r.i;}
    bool operator!=(const Iterator &r) const {return i != r.i;}
    bool operator==(const Iterator &r) const {return i == r.i;}

private:
    Vector<Type>* v;
    int        i;
};