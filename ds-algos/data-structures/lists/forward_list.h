#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <math.h>
#include <new>
#include <forward_list>

template< class Type, class UnqualifiedType  > class Forward_Iterator;
template<class Type, class UnqualifiedType  > class Forward_List;

template <class Type, class UnqualifiedType = std::remove_cv_t<Type>> 
class Node 
{
private:
    
    Node(): data(0), next_node(0) {}
    Node(const UnqualifiedType &value, Node<Type> *ptr= nullptr): data(value), next_node(0) {}
    
    UnqualifiedType  data;
    Node<Type> *next_node;

    friend class Forward_List<Type, UnqualifiedType>;
    friend class Forward_Iterator<Type, UnqualifiedType>;
};

template< class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class Forward_Iterator
{
public:
    using value_type = UnqualifiedType;
    using pointer    = UnqualifiedType*;
    using reference  = UnqualifiedType&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Forward_Iterator(): nodeItr(nullptr) {}   
    Forward_Iterator(Node<Type>* nItr): nodeItr(nItr) {}
    // Default Copy/Move Are Fine.
    Forward_Iterator(Forward_Iterator &it)  = default;
    Forward_Iterator(Forward_Iterator &&it) = default;
    // Default Destructor fine.
    ~Forward_Iterator() = default;

    reference       operator*()             {return this->nodeItr->next_node->data;}
    const reference operator*()       const {return this->nodeItr->next_node->data;}
    pointer         operator->()            {return this->nodeItr; }
    const pointer   operator->()      const {return this->nodeItr;}


    Forward_Iterator& operator++() { // Pre-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        this->nodeItr = this->nodeItr->next_node->next_node;
        return *this;
    }
    // Forward_Iterator& operator--() { // Pre-decrement
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     this->nodeItr = this->nodeItr->prev_node->prev_node;
    //     return *this;
    // }
    Forward_Iterator  operator++(int){ // Post-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Forward_Iterator origItr(*this);
        this->nodeItr = this->nodeItr->next_node->next_node;
        return origItr;
    }
    // Forward_Iterator  operator--(int){ // Post-increment
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     Forward_Iterator origItr(*this);
    //     nodeItr = nodeItr->prev_node->prev_node;
    //     return origItr;
    // }

    Forward_Iterator& operator+=(int n)  {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        while (n && this->nodeItr){
            this->nodeItr = this->nodeItr->next_node->next_node;
            --n;
        }
        return *this;
    }
    // Forward_Iterator& operator-=(int n){
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     while (n && this->nodeItr){
    //         this->nodeItr = this->nodeItr->prev_node->prev_node;
    //         --n;
    //     }
    //     return *this;
    // }

    Forward_Iterator operator+(int n) const {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Forward_Iterator result(*this);
        return result += n;
    }
    // Forward_Iterator operator-(int n) const {
    //     Forward_Iterator result(*this);
    //     return result -= n;
    // }

    difference_type operator-(Forward_Iterator const& rhs) const {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        return 0;
    }

    // Note: comparing Forward_Iterator from different containers
    //       is undefined behavior so we don't need to check
    //       if they are the same container.
    template<class OtherType>
    bool operator<(Forward_Iterator<OtherType> const& rhs)const { return  this->nodeItr <  rhs.nodeItr; }
    template<class OtherType>
    bool operator<=(Forward_Iterator<OtherType> const& rhs)const {return this->nodeItr <= rhs.nodeItr;}
    template<class OtherType>
    bool operator>(Forward_Iterator<OtherType> const& rhs)const {return this->nodeItr >  rhs.nodeItr;}
    template<class OtherType>
    bool operator>=(Forward_Iterator<OtherType> const& rhs)const {return this->nodeItr >= rhs.nodeItr;}
    template<class OtherType>
    bool operator!=(const Forward_Iterator<OtherType> &rhs) const {return this->nodeItr != rhs.nodeItr;}
    template<class OtherType>
    bool operator==(const Forward_Iterator<OtherType> &rhs) const {return this->nodeItr == rhs.nodeItr;}

    operator Forward_Iterator<const Type>() const { return Forward_Iterator<const Type>(this->nodeItr); }

private:
    Node<Type>* nodeItr;
};


template<class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class Forward_List{
public:

    typedef class Forward_Iterator<Type> iterator;
    typedef class Forward_Iterator<const Type> const_iterator;
    
    Forward_List(): first_node(new Node<Type>()), last_node(new Node<Type>()) ,size(0) {this->first_node->next_node = this->last_node;}

    Forward_List(unsigned count, const UnqualifiedType & value)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(count){
        this->first_node->next_node = this->last_node;
        Node<Type> *node_ptr = this->first_node;
        while(count ) {
            Node<Type> *new_node = new Node<Type>(value);
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
            --count;
        }
        node_ptr->next_node = this->last_node;
    }

    Forward_List(unsigned count)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(count) {
        this->first_node->next_node = this->last_node;
        Node<Type> *node_ptr = this->first_node;
        while(count ) {
            Node<Type> *new_node = new Node<Type>();
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
            --count;
        }
        node_ptr->next_node = this->last_node;

    }

    template<class InputIt>
    Forward_List(InputIt first, InputIt last)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(0){
        this->first_node->next_node = this->last_node;
        Node<Type> *node_ptr = this->first_node;
        while(first != last){
            Node<Type> *new_node = new Node<Type>(*first);
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
            ++size;
        }
        node_ptr->next_node = this->last_node;
    }
    
    Forward_List(const Forward_List &other)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(other.size()){
        Forward_List::iterator it (other.begin());
        Node<Type> *node_ptr = this->first_node;
        while (it != other.end()){
            Node<Type> *new_node = new Node<Type>(*first);
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
        }
        node_ptr->next_node = this->last_node;
    }
    Forward_List(const Forward_List &&other)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(other.size()){
        
    }
    ~Forward_List(){
        if(this->first_node){
            Node<Type> *node_ptr = this->first_node;
            
            while(node_ptr) {
                Node<Type> *trash = node_ptr;
                node_ptr = node_ptr->next_node;
                delete trash;
            }

        }
    }
    Forward_List<UnqualifiedType >& operator=(const Forward_List<Type >& other){
        Forward_List<Type> tmp(other);
        tmp.swap(*this);
        return *this;
    }

    Forward_List<Type>& operator=(const Forward_List<Type>&& other) {

    }

    void assign(unsigned count, const Type& value){
        this->resize(count);

    }

    

    //element access
    UnqualifiedType& front() {return  &first_node->value;}
    const UnqualifiedType& front() const {return  &first_node->value;}
    
    typename Forward_List<Type>::iterator begin() {}
    

    //capacity
    unsigned empty() {return size == 0;}
    unsigned max_size(){return UINT_MAX;}

    // modifiers
    void clear() noexcept{
        if(this->first_node){
            Node<Type> *node_ptr = this->first_node;
            
            while(node_ptr) {
                Node<Type> *trash = node_ptr;
                node_ptr = node_ptr->next_node;
                delete trash;
            }
        }
        first_node = new Node<Type>();
        last_node = new Node<Type>();
        first_node->next_node = last_node;
    }
    iterator insert_after(const_iterator pos, const UnqualifiedType &value) {
        
    }
    iterator insert_after(const_iterator pos, const UnqualifiedType &&value);
    iterator insert_after(const_iterator pos, unsigned count, const UnqualifiedType &value);
    template<class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    // template< class... Args >
    // iterator emplace_after( const_iterator pos, Args&&... args );
    iterator erase_after(iterator pos);
    iterator erase_after(iterator first, iterator last);
    void push_front(const UnqualifiedType & value);
    void push_front(UnqualifiedType && value);
    // template< class... Args >
    // void emplace_front( Args&&... args );
    // template< class... Args >
    // reference emplace_front( Args&&... args );
    void pop_front();
    void resize(unsigned count);
    void resize(unsigned count, const UnqualifiedType & value);
    void swap(Forward_List<Type>& other);
    //void swap(Forward_List& other) noexcept;

    //operations
    void merge(Forward_List<Type>& other);
    void merge(Forward_List<Type>&& other);
    // template <class Compare>
    // void merge( forward_list& other, Compare comp );
    // template <class Compare>
    // void merge( forward_list&& other, Compare comp );
    void splice_after(iterator pos, Forward_List<Type> &other);
    void splice_after(iterator pos, Forward_List<Type> &&other);
    void splice_after(iterator pos, Forward_List<Type> &other, iterator it);
    void splice_after(iterator pos, Forward_List<Type> &&other, iterator it);
    void splice_after(iterator pos, Forward_List<Type> &other, iterator first, iterator last);
    void splice_after(iterator pos, Forward_List<Type> &&other, iterator first, iterator last);
    unsigned remove(const UnqualifiedType & value);
    void reverse() noexcept;
    unsigned unique();
    void sort();
    // template< class Compare >
    // void sort( Compare comp );


    //non-member operators
    friend bool operator==(const Forward_List<Type> &l1, const Forward_List<Type> &l2) { }
    friend bool operator!=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator<(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator<=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator>(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator>=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    //friend Forward_List<Type> operator+(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend std::ostream& operator<<(std::ostream &os, const Forward_List<Type> &l) {
        s.put('[');
        char arrow[3] = {'\0', ' ', '\0'};
        for (const auto& e : v) {
            s << comma << e;
            arrow[0] = '->';
        }
        return s << ']';
    }
    friend std::istream& operator>>(std::istream &is, const Forward_List<Type> &l) {}




protected:
    Node<Type> *first_node;
    Node<Type> *last_node;
    unsigned size;
    
};




#endif // FORWARD_LIST_H