#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <iostream>
#include <cassert>      // assert
#include <algorithm>
#include <climits>
#include <math.h>
#include <vector>

template< class Type, class UnqualifiedType > class Bidir_Iterator;
template<class Type, class UnqualifiedType  > class List;

template <class Type, class UnqualifiedType = std::remove_cv_t<Type>> 
class Node 
{
public:
    Node(): data(0), next_node(0), prev_node(0) {}
    Node(const UnqualifiedType &value, Node<Type> *ptr= nullptr): data(value), next_node(0) {}
    
    UnqualifiedType  data;
    Node<Type> *next_node;
    Node<Type> *prev_node;

    friend class List<Type, UnqualifiedType>;
    friend class Bidir_Iterator<Type, UnqualifiedType>;
};

template< class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class Bidir_Iterator
{
public:
    using value_type = UnqualifiedType;
    using pointer    = UnqualifiedType*;
    using reference  = UnqualifiedType&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Bidir_Iterator(): nodeItr(nullptr) {}   
    Bidir_Iterator(Node<Type>* nItr): nodeItr(nItr) {}
    // Default Copy/Move Are Fine.
    Bidir_Iterator(const Bidir_Iterator &it)  = default;
    Bidir_Iterator(Bidir_Iterator &&it) = default;
    // Default Destructor fine.
    ~Bidir_Iterator() = default;

    Bidir_Iterator& operator=(const Bidir_Iterator &other) {
        Bidir_Iterator tmpItr(other);
        tmpItr.swap(*this);
        return *this;
    }

    Node<Type>*       operator*()             {return this->nodeItr;}
    const Node<Type>* operator*()       const {return this->nodeItr;}
    Node<Type>*         operator->()            {return this->nodeItr; }
    const Node<Type>*   operator->()      const {return this->nodeItr;}


    Bidir_Iterator& operator++() { // Pre-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        this->nodeItr = this->nodeItr->next_node;
        return *this;
    }
    Bidir_Iterator& operator--() { // Pre-decrement
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        this->nodeItr = this->nodeItr->prev_node;
        return *this;
    }
    Bidir_Iterator  operator++(int){ // Post-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Bidir_Iterator origItr(*this);
        this->nodeItr = this->nodeItr->next_node;
        return origItr;
    }
    Bidir_Iterator  operator--(int){ // Post-increment
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Bidir_Iterator origItr(*this);
        nodeItr = nodeItr->prev_node;
        return origItr;
    }

    Bidir_Iterator& operator+=(int n)  {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        while (n && this->nodeItr){
            this->nodeItr = this->nodeItr->next_node;
            --n;
        }
        return *this;
    }
    Bidir_Iterator& operator-=(int n){
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        while (n && this->nodeItr){
            this->nodeItr = this->nodeItr->prev_node;
            --n;
        }
        return *this;
    }

    Bidir_Iterator operator+(int n) const {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        Bidir_Iterator result(*this);
        return result += n;
    }
    Bidir_Iterator operator-(int n) const {
        Bidir_Iterator result(*this);
        return result -= n;
    }

    difference_type operator-(Bidir_Iterator const& rhs) const {
        assert(this->nodeItr != nullptr && "Out-of-bounds iterator increment!");
        return 0;
    }

    // Note: comparing Bidir_Iterator from different containers
    //       is undefined behavior so we don't need to check
    //       if they are the same container.
    template<class OtherType>
    bool operator<(Bidir_Iterator<OtherType> const& rhs)const { return  this->nodeItr <  rhs.nodeItr; }
    template<class OtherType>
    bool operator<=(Bidir_Iterator<OtherType> const& rhs)const {return this->nodeItr <= rhs.nodeItr;}
    template<class OtherType>
    bool operator>(Bidir_Iterator<OtherType> const& rhs)const {return this->nodeItr >  rhs.nodeItr;}
    template<class OtherType>
    bool operator>=(Bidir_Iterator<OtherType> const& rhs)const {return this->nodeItr >= rhs.nodeItr;}
    template<class OtherType>
    bool operator!=(const Bidir_Iterator<OtherType> &rhs) const {return this->nodeItr != rhs.nodeItr;}
    template<class OtherType>
    bool operator==(const Bidir_Iterator<OtherType> &rhs) const {return this->nodeItr == rhs.nodeItr;}

    operator Bidir_Iterator<const Type>() const { return Bidir_Iterator<const Type>(this->nodeItr); }

    void swap(Bidir_Iterator<Type>& other) noexcept{
        using std::swap;
        swap(this->nodeItr, other.nodeItr);
    }

private:
    Node<Type>* nodeItr;
};


template<class Type, class UnqualifiedType = std::remove_cv_t<Type> >
class List{
public:

    typedef Bidir_Iterator<UnqualifiedType> iterator;
    typedef const  Bidir_Iterator<UnqualifiedType> const_iterator;
    
    List()
    : first_node(new Node<Type>()), last_node(new Node<Type>()) ,size(0) {
        this->first_node->next_node = this->last_node;
        this->last_node->prev_node = this->first_node;
    }

    List(unsigned count, const UnqualifiedType & value)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(count){
        Node<Type> *node_ptr = this->first_node;
        while(count ) {
            Node<Type> *new_node = new Node<Type>(value);
            node_ptr->next_node = new_node;
            new_node->prev_node = node_ptr;
            node_ptr = node_ptr->next_node;
            --count;
        }
        node_ptr->next_node = this->last_node;
        this->last_node->prev_node = node_ptr; 
    }

    List(unsigned count)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(count) {
        Node<Type> *node_ptr = this->first_node;
        while(count ) {
            Node<Type> *new_node = new Node<Type>();
            node_ptr->next_node = new_node;
            new_node->prev_node = node_ptr;
            node_ptr = node_ptr->next_node;
            --count;
        }
        node_ptr->next_node = this->last_node;
        this->last_node->prev_node = node_ptr; 
    }

    
    List(Bidir_Iterator<Type> first, Bidir_Iterator<Type> last)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(0){
        Node<Type> *node_ptr = this->first_node;
        while(first != last){
            Node<Type> *new_node = new Node<Type>(first->data);
            node_ptr->next_node = new_node;
            new_node->prev_node = node_ptr;
            node_ptr = node_ptr->next_node;
            ++size;
            ++first;
        }
        node_ptr->next_node = this->last_node;
        this->last_node->prev_node = node_ptr;
    }
    
    List(const List &other)
    : first_node(new Node<Type>()), last_node(new Node<Type>()), size(other.size){
        List::iterator it (other.begin());
        Node<Type> *node_ptr = this->first_node;
        while (it != other.end()){
            Node<Type> *new_node = new Node<Type>((it->data));
            node_ptr->next_node = new_node;
            new_node->prev_node = node_ptr;
            node_ptr = node_ptr->next_node;
            ++it;
        }
        node_ptr->next_node = this->last_node;
        this->last_node->prev_node = node_ptr;
    }
    List(const List &&other)
    : size(other.size()){
        this->first_node = other.first_node;
        other.first_node = nullptr;
    }
    ~List(){
        if(this->first_node){
            Node<Type> *node_ptr = this->first_node;
            
            while(node_ptr) {
                Node<Type> *trash = node_ptr;
                node_ptr = node_ptr->next_node;
                delete trash;
                trash = nullptr;
            }

        }
    }
    List<UnqualifiedType >& operator=(const List<Type>& other){
        List<Type> tmp(other);
        tmp.swap(*this);
        return *this;
    }

    List<Type>& operator=(const List<Type>&& other) {

    }

    void assign(unsigned count, const UnqualifiedType& value){ this->resize(count, value); }

    

    //element access
    UnqualifiedType& front() {return  this->begin()->data;}
    const UnqualifiedType& front() const {return  this->begin()->data;}
    UnqualifiedType& back() {return  (this->end()-1)->data;}
    const UnqualifiedType& back() const {return  (this->begin()-1)->data;}
    
    // iterators
    
    iterator begin() noexcept {return iterator(first_node)+1;}
    const_iterator begin() const noexcept{return const_iterator(first_node)+1;}
    const_iterator cbegin() const noexcept{return const_iterator(first_node)+1;}
    
    iterator end() noexcept{return iterator(last_node);}
    const_iterator end() const noexcept{return const_iterator(last_node);}
    const_iterator cend() const noexcept{return const_iterator(last_node);}
    
    //capacity
    unsigned empty() const {return size == 0;}
    //unsigned size() const {return this->size;}
    unsigned max_size() const {return UINT_MAX;}

    // modifiers
    void clear() noexcept{
        if(this->first_node){
            Node<Type> *node_ptr = this->first_node;
            
            while(node_ptr ) {
                Node<Type> *trash = node_ptr;
                node_ptr = node_ptr->next_node;
                delete trash;
                trash = nullptr;
            }
        }
        this->size = 0;
        first_node = new Node<Type>();
        last_node = new Node<Type>();
        this->first_node->next_node = this->last_node;
        this->last_node->prev_node = this->first_node;
    }
    iterator insert(const_iterator pos, const UnqualifiedType &value) {
        if(*pos == this->first_node) return this->begin();
        Node<Type> *new_node = new Node<Type>(value);
        Node<Type> *prev_insert_node = pos->prev_node;
        prev_insert_node->next_node = new_node;
        new_node->prev_node = prev_insert_node;
        new_node->next_node = *iterator(pos);
        iterator(pos)->prev_node = new_node; 
        ++this->size;
        return iterator(new_node);
    }
    iterator insert(const_iterator pos, const UnqualifiedType &&value){
        const UnqualifiedType v = std::move(value);
        return insert(pos, v);
    }
    iterator insert(const_iterator pos, unsigned count, const UnqualifiedType &value){
        if(count == 0 || *pos == this->first_node) return pos;
        iterator saveStart = pos-1;
        iterator it = pos;
        for(unsigned i = 0; i < count; ++i) it = insert(it, value);
        return saveStart+1;
    }

    //template<class InputIt>
    //iterator insert(const_iterator pos, InputIt first, InputIt last);
    // template< class... Args >
    // iterator emplace_after( const_iterator pos, Args&&... args );
    iterator erase(const_iterator pos){
        if(pos == this->end() || *pos == this->first_node || *pos == nullptr) return this->end();
        Node<Type> *trash = *(iterator(pos));
        Node<Type> *next_to_trash = trash->next_node;
        Node<Type> *prev_to_trash = trash->prev_node;
        prev_to_trash->next_node = next_to_trash;
        next_to_trash->prev_node = prev_to_trash;
        if(trash) {
            delete trash;
            trash = nullptr;
            --this->size;
        }
        return iterator(next_to_trash);
    }
    iterator erase(const_iterator first, const_iterator last){
        if(first == this->end() || first == last) return this->end();
        Node<Type> *trash_begin = *(iterator(first));
        Node<Type> *trash_end = *(iterator(last) -1 );
        trash_begin->prev_node->next_node = *(iterator(last));
        iterator(last)->prev_node = trash_begin->prev_node;
        while(trash_begin != *last && trash_begin){
            Node<Type> *trash = trash_begin;
            trash_begin = trash_begin->next_node;
            delete trash;
            trash = nullptr;
            --this->size;
        }
        return last;
    }

    void push_back(const UnqualifiedType &value){
        Node<Type> *new_node = new Node<Type>(value);
        Node<Type> *prev_last = this->last_node->prev_node;
        prev_last->next_node = new_node;
        new_node->prev_node = prev_last;
        new_node->next_node = this->last_node;
        this->last_node->prev_node = new_node;
        ++this->size;
    }
    void push_back(UnqualifiedType &&value){
        UnqualifiedType v= std::move(value);
        push_back(v);
    }

    void pop_back(){
        Node<Type> *trash = this->last_node->prev_node;
        if(trash != this->first_node){
            trash->prev_node->next_node = this->last_node;
            this->last_node->prev_node = trash->prev_node;
            delete trash;
            trash = nullptr;
            --this->size;
        }
    }
    

    void push_front(const UnqualifiedType & value){
        Node<Type> *node = new Node<Type>(value);
        node->next_node = this->first_node->next_node;
        node->prev_node = this->first_node;
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
            this->first_node->next_node->prev_node = trash->prev_node;
            delete trash;
            trash = nullptr;
            --this->size;
        }
    }
    void resize(unsigned count) {
        
        
        unsigned c = 0;
        if(count > this->size){
            c = count - this->size;
            while(c--) this->insert(this->end(),0);
        } else if (count < this->size){
            c = count;
            iterator it = this->begin();
            while(c--) ++it;
            this->erase(it, this->end());
        }
        this->size = count;
    }
    void resize(unsigned count, const UnqualifiedType & value){
        
        unsigned c = 0;
        if(count > this->size){
            c = count - this->size;
            while(c--) this->insert(this->end(),value);
        } else if (count < this->size){
            c = count;
            iterator it = this->begin();
            while(c--) ++it;
            this->erase(it, this->end());
        }
        this->size = count;
    }
    void swap(List<Type>& other) noexcept{
        using std::swap;
        swap(this->size, other.size);
        swap(this->first_node, other.first_node);
    }

    //operations
    void merge(List<Type>& other){
        Node<Type> *node_ptr = this->first_node;
        Node<Type> *other_node_ptr = *(other.before_begin());
        
        while (node_ptr->next_node != this->last_node && 
              other_node_ptr->next_node != *(other.end())){
            
            if(other_node_ptr->next_node->data <= node_ptr->next_node->data){
                Node<Type> *other_target = other_node_ptr->next_node;
                Node<Type> *other_target_next =  other_target->next_node;
                other_node_ptr->next_node = other_target_next;

                Node<Type> *this_insert_next = node_ptr->next_node;
                node_ptr->next_node = other_target;
                other_target->next_node = this_insert_next; 
            } 
            node_ptr = node_ptr->next_node;
        }
        if(other_node_ptr->next_node != *(other.end())) {
            node_ptr->next_node =  other_node_ptr->next_node;
            other_node_ptr->next_node = this->last_node;
            this->last_node = *(other.end()); 
        }

        
        
    }
    void merge(List<Type>&& other){
        List l(std::move(other));
        merge(l);
    }
    // template <class Compare>
    // void merge( List& other, Compare comp );
    // template <class Compare>
    // void merge( List&& other, Compare comp );
    void splice_after(iterator pos, List<Type> &other){
        auto otherIt = other.begin();
        while(otherIt != other.end()) {
            insert_after(pos, otherIt->data);
            ++pos;
            ++otherIt;
        }
    }
    void splice_after(iterator pos, List<Type> &&other){
        List l(std::move(other));
        splice_after(pos, l);
    }
    void splice_after(iterator pos, List<Type> &other, iterator it){
        auto otherIt = it + 1;
        while(otherIt != other.end()) {
            insert_after(pos, otherIt->data);
            ++pos;
            ++otherIt;
        }
    }
    void splice_after(iterator pos, List<Type> &&other, iterator it){
        List l(std::move(other));
        splice_after(pos, l, it);
    }
    void splice_after(iterator pos, List<Type> &other, iterator first, iterator last){
        auto otherIt = first + 1;
        while(otherIt != last) {
            insert_after(pos, otherIt->data);
            ++pos;
            ++otherIt;
        }
    }
    void splice_after(iterator pos, List<Type> &&other, iterator first, iterator last){
        List l(std::move(other));
        splice_after(pos, l, first, last);
    }

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
    unsigned unique(){
        Node<Type> *node_ptr = *(this->begin());
        while(node_ptr->next_node != this->last_node){
            if(node_ptr->next_node->data == node_ptr->data) erase_after(iterator(node_ptr));
            node_ptr = node_ptr->next_node;
        }
    }
    void sort(){
        std::vector<Type> v(this->size);
        iterator it = this->begin();
        for(unsigned i =0; i < v.size() && it != this->end(); ++i) {v.at(i) = it->data; ++it;}
        std::sort(v.begin(), v.end());
        Node<Type> *node_ptr = this->first_node->next_node;
        unsigned i = 0;
        while(node_ptr != this->last_node && i < v.size()) {node_ptr->data = v.at(i++); node_ptr = node_ptr->next_node;} 
    }
    // template< class Compare >
    // void sort( Compare comp );


    //non-member operators
    friend bool operator==(const List<Type> &l1, const List<Type> &l2) { 
        auto it1 = l1.begin();
        auto it2 = l2.begin();
        while(it1++ != l1.end() && it2++ != l2.end()) if(it1->data != it2->data) return false;
        return true;
    }
    friend bool operator!=(const List<Type> &l1, const List<Type> &l2) {
        auto it1 = l1.begin();
        auto it2 = l2.begin();
        while(it1++ != l1.end() && it2++ != l2.end()) if(it1->data != it2->data) return true;
        return false;
    }
    //friend List<Type> operator+(const List<Type> &l1, const List<Type> &l2) {}

    
    friend std::ostream& operator<<(std::ostream &os, const List<Type> &l) {
        
        os.put('[');
        char arrow[3] = {'\0', ' ','\0'};
        for (auto it = l.begin(); it != l.end(); ++it) {
            os << arrow << it->data;
            arrow[0] = '<';
            arrow[1] = '-';
            arrow[2] = '>';
        }
        return os << ']';
    }
    friend std::istream& operator>>(std::istream &is, const List<Type> &l) {}



protected:
    Node<Type> *first_node;
    Node<Type> *last_node;
    unsigned size;
    
};




#endif // LIST_H