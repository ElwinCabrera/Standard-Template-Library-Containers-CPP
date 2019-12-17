#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdexcept>
#include <iostream>
#include <cassert>      // assert
#include <algorithm>
#include <climits>
#include <math.h>

template< class Type, class UnqualifiedType > class Forward_Iterator;
template<class Type, class UnqualifiedType  > class Forward_List;

template <class Type, class UnqualifiedType = std::remove_cv_t<Type>> 
class Node 
{
public:
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
    Forward_Iterator(const Forward_Iterator &it)  = default;
    Forward_Iterator(Forward_Iterator &&it) = default;
    // Default Destructor fine.
    ~Forward_Iterator() = default;

    Forward_Iterator& operator=(const Forward_Iterator &other) {
        Forward_Iterator tmpItr(other);
        tmpItr.swap(*this);
        return *this;
    }

    Node<Type>*       operator*()             {return this->nodeItr;}
    const Node<Type>* operator*()       const {return this->nodeItr;}
    Node<Type>*         operator->()            {return this->nodeItr; }
    const Node<Type>*   operator->()      const {return this->nodeItr;}


    Forward_Iterator& operator++() { // Pre-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        this->nodeItr = this->nodeItr->next_node;
        return *this;
    }
    // Forward_Iterator& operator--() { // Pre-decrement
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     this->nodeItr = this->nodeItr->prev_node;
    //     return *this;
    // }
    Forward_Iterator  operator++(int){ // Post-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Forward_Iterator origItr(*this);
        this->nodeItr = this->nodeItr->next_node;
        return origItr;
    }
    // Forward_Iterator  operator--(int){ // Post-increment
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     Forward_Iterator origItr(*this);
    //     nodeItr = nodeItr->prev_node;
    //     return origItr;
    // }

    Forward_Iterator& operator+=(int n)  {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        while (n && this->nodeItr){
            this->nodeItr = this->nodeItr->next_node;
            --n;
        }
        return *this;
    }
    // Forward_Iterator& operator-=(int n){
    //     assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
    //     while (n && this->nodeItr){
    //         this->nodeItr = this->nodeItr->prev_node;
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

    void swap(Forward_Iterator<Type>& other) noexcept{
        using std::swap;
        swap(this->nodeItr, other.nodeItr);
    }

private:
    Node<Type>* nodeItr;
};


template<class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class Forward_List{
public:

    typedef Forward_Iterator<UnqualifiedType> iterator;
    typedef const  Forward_Iterator<UnqualifiedType> const_iterator;
    
    Forward_List(): first_node(new Node<Type>()), last_node(new Node<Type>()) ,size(0) {this->first_node->next_node = this->last_node;}

    Forward_List(unsigned count, const UnqualifiedType & value)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(count){
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
        Node<Type> *node_ptr = this->first_node;
        while(count ) {
            Node<Type> *new_node = new Node<Type>();
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
            --count;
        }
        node_ptr->next_node = this->last_node;

    }

    
    Forward_List(Forward_Iterator<Type> first, Forward_Iterator<Type> last)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(0){
        this->first_node->next_node = this->last_node;
        Node<Type> *node_ptr = this->first_node;
        while(first != last){
            Node<Type> *new_node = new Node<Type>(first->data);
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
            Node<Type> *new_node = new Node<Type>(*it);
            node_ptr->next_node = new_node;
            node_ptr = node_ptr->next_node;
            it++;
        }
        node_ptr->next_node = this->last_node;
    }
    Forward_List(const Forward_List &&other)
    : size(other.size()){
        this->first_node = other.first_node;
        other.first_node = nullptr;
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
    Forward_List<UnqualifiedType >& operator=(const Forward_List<Type>& other){
        Forward_List<Type> tmp(other);
        tmp.swap(*this);
        return *this;
    }

    Forward_List<Type>& operator=(const Forward_List<Type>&& other) {

    }

    void assign(unsigned count, const UnqualifiedType& value){ this->resize(count, value); }

    

    //element access
    UnqualifiedType& front() {return  this->begin()->data;}
    const UnqualifiedType& front() const {return  this->begin()->data;}
    
    // iterators
    iterator before_begin() noexcept {return iterator(this->first_node);}
    const iterator before_begin() const noexcept {return const_iterator(this->first_node);}
    const iterator cbefore_begin() const noexcept {return const_iterator(this->first_node);}
    
    iterator begin() noexcept {return iterator(first_node)+1;}
    const_iterator begin() const noexcept{return const_iterator(first_node)+1;}
    const_iterator cbegin() const noexcept{return const_iterator(first_node)+1;}
    
    iterator end() noexcept{return iterator(last_node);}
    const_iterator end() const noexcept{return const_iterator(last_node);}
    const_iterator cend() const noexcept{return const_iterator(last_node);}
    
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
        this->size = 0;
        first_node = new Node<Type>();
        last_node = new Node<Type>();
        first_node->next_node = last_node;
    }
    iterator insert_after(const_iterator pos, const UnqualifiedType &value) {
        iterator p = pos;
        iterator next = pos + 1;
        Node<Type> *node = new Node<Type>(value);
        if(next != this->end()){
            p->next_node = node;
            node->next_node = *next;
        } else {
            p->next_node = node;
            node->next_node = last_node;
        }
        ++this->size;
        return next;
    }
    iterator insert_after(const_iterator pos, const UnqualifiedType &&value){
        const UnqualifiedType v = std::move(value);
        return insert_after(pos, v);
    }
    iterator insert_after(const_iterator pos, unsigned count, const UnqualifiedType &value){
        for(const_iterator it = pos; it != pos + count; ++it) insert_after(it, value);
    }

    template<class InputIt>
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    // template< class... Args >
    // iterator emplace_after( const_iterator pos, Args&&... args );
    iterator erase_after(const_iterator pos){
        if(pos == this->end() || (pos +1) == this->end() || *pos == nullptr) return this->end();
        iterator curr = pos;
        iterator trash = pos + 1;
        iterator next = trash->next_node;
        curr->next_node = *next;
        if(*trash) {
            trash->next_node = nullptr;
            delete *trash;
            --this->size;
        }
        return next;
    }
    iterator erase_after(const_iterator first, const_iterator last){
        iterator it = first + 1;
        iterator firstIt = first;
        iterator lastIt = last;
        firstIt->next_node = *lastIt;  
             
        while(it != last){
            iterator trash = it;
            iterator next = trash->next_node;
            if(*trash) {
                trash->next_node = nullptr;
                delete *trash;
                --this->size;
            }
            it = next;
        }
        firstIt->next_node =  *lastIt;
        return last;
    }
    

    void push_front(const UnqualifiedType & value){
        Node<Type> *node = new Node<Type>(value);
        node->next_node = this->first_node->next_node;
        this->first_node->next_node = node;
        ++this->size;
    }

    void push_front(UnqualifiedType && value){
        UnqualifiedType v= std::move(value);
        push_front(v);
    }

    // template< class... Args >
    // void emplace_front( Args&&... args );
    // template< class... Args >
    // reference emplace_front( Args&&... args );
    void pop_front(){
        Node<Type> *trash = this->first_node->next_node;
        if(trash && trash != this->last_node){
            this->first_node->next_node = trash->next_node;
            delete trash;
            --this->size;
        }
    }
    void resize(unsigned count) {
        
        iterator it = this->begin();
        unsigned c = 0;
        if(count > this->size){
            c = count - this->size;
            while(it + 1 != this->end()) ++it;
            while(c--) this->insert_after(it,0);
        } else if (count < this->size){
            c = count;
            while(--c) ++it;
            this->erase_after(it, this->end());
        }
        this->size = count;
    }
    void resize(unsigned count, const UnqualifiedType & value){
        
        iterator it = this->begin();
        unsigned c = 0;
        if(count > this->size){
            c = count - this->size;
            while(it + 1 != this->end()) ++it;
            while(c--) this->insert_after(it,value);
        } else if (count < this->size){
            c = count;
            while(--c) ++it;
            this->erase_after(it, this->end());
        }
        this->size = count;
    }
    void swap(Forward_List<Type>& other) noexcept{
        using std::swap;
        swap(this->size, other.size);
        swap(this->first_node, other.first_node);
    }
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

    unsigned remove(const UnqualifiedType & value){
        unsigned count = 0;
        if((this->before_begin() +1)->data == value && (this->before_begin() +1) != this->end()) { erase_after(this->before_begin()); ++count; }
        iterator it = this->begin();
        while(it +1  != this->end()){
            if((it+1)->data == value){ erase_after(it); ++count; }
            else ++it; 
        }
        this->size -= count;
        return count;
    }
    void reverse() noexcept{
        Node<Type> *before_begin = nullptr;
        Node<Type> *begin = this->first_node;
        Node<Type> *after_begin = begin->next_node;

        while(begin ){
            begin->next_node = before_begin;
            before_begin = begin;
            begin = after_begin;

            if(after_begin ) after_begin = after_begin->next_node;
        }
        Node<Type> *tmp = this->first_node;
        this->first_node =  last_node;
        last_node = tmp;
    }
    unsigned unique();
    void sort();
    // template< class Compare >
    // void sort( Compare comp );


    //non-member operators
    friend bool operator==(const Forward_List<Type> &l1, const Forward_List<Type> &l2) { 
        auto it1 = l1.begin();
        auto it2 = l2.begin();
        while(it1++ != l1.end() && it2++ != l2.end()) if(it1->data != it2->data) return false;
        return true;
    }
    friend bool operator!=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {
        auto it1 = l1.begin();
        auto it2 = l2.begin();
        while(it1++ != l1.end() && it2++ != l2.end()) if(it1->data != it2->data) return true;
        return false;
    }
    friend bool operator<(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator<=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator>(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    friend bool operator>=(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}
    //friend Forward_List<Type> operator+(const Forward_List<Type> &l1, const Forward_List<Type> &l2) {}

    
    friend std::ostream& operator<<(std::ostream &os, const Forward_List<Type> &l) {
        
        os.put('[');
        char arrow[2] = {'\0', ' '};
        for (auto it = l.begin(); it != l.end(); ++it) {
            os << arrow << it->data;
            arrow[0] = '-';
            arrow[1] = '>';
        }
        return os << ']';
    }
    friend std::istream& operator>>(std::istream &is, const Forward_List<Type> &l) {}




protected:
    Node<Type> *first_node;
    Node<Type> *last_node;
    unsigned size;
    
};




#endif // FORWARD_LIST_H