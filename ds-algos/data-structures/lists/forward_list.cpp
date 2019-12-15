#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <math.h>
#include <new>
#include <forward_list>

template <class Value_Type> 
class Node 
{
private:
    
    Node(const Value_Type & x): value(x), next_link(0), prev_link(0) {}

    Value_Type value;     
    Node<Value_Type> *next_node;

    friend class Forward_List<Value_Type>;
    //friend class List_iterator<Value_Type>;
};

template<class Value_Type>
class Forward_List{
public:
    typedef Value_Type* iterator; 
    Forward_List();
    Forward_List(unsigned count, const Value_Type& value);
    Forward_List(unsigned count);
    Forward_List(iterator first, iterator last);
    Forward_List(const Forward_List &other);
    Forward_List(const Forward_List &&other);
    ~Forward_List();
    Forward_List<Value_Type>& operator=(const Forward_List<Value_Type>& other);
    Forward_List<Value_Type>& operator=(const Forward_List<Value_Type>&& other) {}
    void assign(unsigned count, const Value_Type& value);

    //non-member operators
    friend bool operator==(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend bool operator!=(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend bool operator<(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend bool operator<=(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend bool operator>(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend bool operator>=(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    //friend Forward_List<Value_Type> operator+(const Forward_List<Value_Type> &l1, const Forward_List<Value_Type> &l2);
    friend std::ostream& operator<<(std::ostream &os, const Forward_List<Value_Type> &l);
    friend std::istream& operator>>(std::istream &is, const Forward_List<Value_Type> &l);

    //element access
    Value_Type& front() {return  &first_node->value}

    //capacity
    unsigned empty() {return size == 0;}
    unsigned max_size(){return UINT_MAX;}

    // modifiers
    void clear() noexcept;
    iterator insert_after(iterator pos, const Value_Type& value);
    iterator insert_after(iterator pos, const Value_Type&& value);
    iterator insert_after(iterator pos, unsigned pos, const Value_Type& value);
    // template< class... Args >
    // iterator emplace_after( const_iterator pos, Args&&... args );
    iterator erase_after(iterator pos);
    iterator erase_after(iterator first, iterator last);
    void push_front(const Value_Type& value);
    void push_front(Value_Type&& value);
    // template< class... Args >
    // void emplace_front( Args&&... args );
    // template< class... Args >
    // reference emplace_front( Args&&... args );
    void pop_front();
    void resize(unsigned count);
    void resize(unsigned count, const Value_Type& value);
    void swap(Forward_List<Value_Type>& other);
    //void swap(Forward_List& other) noexcept;

    //operations
    void merge(Forward_List<Value_Type>& other);
    void merge(Forward_List<Value_Type>&& other);
    // template <class Compare>
    // void merge( forward_list& other, Compare comp );
    // template <class Compare>
    // void merge( forward_list&& other, Compare comp );
    void splice_after(iterator pos, Forward_List<Value_Type> &other);
    void splice_after(iterator pos, Forward_List<Value_Type> &&other);
    void splice_after(iterator pos, Forward_List<Value_Type> &other, iterator it);
    void splice_after(iterator pos, Forward_List<Value_Type> &&other, iterator it);
    void splice_after(iterator pos, Forward_List<Value_Type> &other, iterator first, iterator last);
    void splice_after(iterator pos, Forward_List<Value_Type> &&other, iterator first, iterator last);
    void remove(const Value_Type& value);
    unsigned remove(const Value_Type& value);
    void reverse() noexcept;
    void unique();
    unsigned unique();
    void sort();
    // template< class Compare >
    // void sort( Compare comp );





protected:
    Node<Value_Type> *first_node;
    Node<Value_Type> *last_node;
    Value_Type value;
    unsigned size;
};