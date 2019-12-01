
/*
Operation 	    Speed
vector() 	    O(1)
vector(n, x) 	O(n)
size() 	        O(1)
v[ i ] 	        O(1)
push_back(x) 	O(1)
pop_back 	    O(1)
insert 	        O(size())
erase 	        O(size())
front, back 	O(1)
*/
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <string>
using std::cout;
using std::endl;

template<class T>
class CustomVector{
    
private:
    unsigned int currCapacity;
    unsigned int vectSize;

    T *buffer;
public:
    typedef  T *iterator;
    CustomVector();//
    CustomVector(unsigned int size);//
    CustomVector(unsigned int size, const T &type);//
    CustomVector(const CustomVector<T> &v);//
    CustomVector(CustomVector<T> &&other) noexcept ;
    ~CustomVector();//
    CustomVector<T>& operator=(const CustomVector<T> &v);//
    CustomVector<T>& operator=(CustomVector<T> &&other);

    iterator begin();//
    iterator end();//
    /*iterator rbegin();
    iterator rend();
    iterator cbegin() const;
    iterator cend() const;
    iterator crbegin() const;
    iterator crend() const;*/


    
    unsigned int size() const;//
    unsigned int max_size() const;//
    void resize();//
    unsigned int capacity() const;//
    bool empty() const;//
    void reserve(unsigned int cap);//
    void shrink_to_fit();

    T& operator[](unsigned int idx);//
    T& operator[](unsigned int idx) const;//
    T& at(unsigned int idx);//
    T& at(unsigned int idx) const;//
    T& front() const;//
    T& back() const;//
    T* data() const;

    void assign(unsigned int count, const T &value);
    void push_back(const T &item);//
    void push_front(const T &item);//
    void pop_back();//
    void insert(iterator it, const T &item);
    void insert(unsigned int pos, const T &item);
    void erase(iterator pos);//
    void erase(iterator first, iterator last);
    void resize(unsigned int size);//
    void swap(CustomVector<T> &otherV) noexcept;
    void clear();//

    template<class ... Args>
    void emplace(iterator it,Args&& ... args){
        //T newT(std::forward<Args>(args)...));
        T *newT = new (it) T(std::forward<Args>(args)...);
        //push_back(new (*this) T(std::forward<Args>(args)...));
    }
    template<class ... Args>
    void emplace_back(Args&& ... args){
        //T newT(std::forward<Args>(args)...));
        if(vectSize == currCapacity){
            if(vectSize == 0) reserve(1);
            else reserve(2 * currCapacity);
        }
        T *newT = new (end()) T(std::forward<Args>(args)...);
        //push_back(new (*this) T(std::forward<Args>(args)...));
        ++vectSize;
    }
    //void get_allocator
};


/** Constructors and Destructors **/
template<typename T>
CustomVector<T>::CustomVector(){
    cout << "In Constructor #1"<<"\n";
    currCapacity = 0;
    vectSize = 0;
    buffer = nullptr;
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size){
    cout << "In Constructor #2"<<"\n";
    buffer = nullptr;
    this->vectSize = size;
    reserve(size);
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size, const T &item){
    
    cout << "In Constructor #3"<<"\n";
    if(this->buffer != nullptr) this->buffer = nullptr;
    reserve(size);
    this->vectSize = size;
    for(unsigned int i = 0; i < size; i++) memcpy(buffer+i, &item, sizeof(item));
}

template<typename T>
CustomVector<T>::CustomVector( const CustomVector<T> &other){
    cout << "In Copy Constructor #4"<<"\n";
    this->buffer = nullptr;
    reserve(other.size());
    vectSize = other.size();
    for(unsigned int i = 0; i < other.size(); i++) buffer[i] = other.buffer[i];
}

template<typename T>
CustomVector<T>::CustomVector(CustomVector<T> &&other) noexcept {
    cout << "In Move Constructor #5"<<"\n";
    buffer = other->buffer;
    other->buffer = nullptr;
}

template<typename T>
CustomVector<T>::~CustomVector(){
    cout << "In Custom Vector Destructor "<<"\n";
    if(buffer != nullptr) {
        delete[] buffer;
        buffer = nullptr;
    }
}

template<typename T>
CustomVector<T>& CustomVector<T>::operator=(const CustomVector<T> &other){
    cout << "In operator= (...)"<<"\n";
    CustomVector<T> tmpCpy(other);
    tmpCpy.swap(*this);
    return *this;
}
template<typename T>
CustomVector<T>& CustomVector<T>::operator=(CustomVector<T> &&other){

}
 
/** Iterators **/
template<typename T>
typename CustomVector<T>::iterator CustomVector<T>::begin(){
    return buffer;
}

template<typename T>
typename CustomVector<T>::iterator CustomVector<T>::end(){
    return buffer + size();
}


/** Capacity Functions **/
template<typename T>
unsigned int CustomVector<T>::size() const {
    //cout << "In size()"<<"\n";
    return vectSize;
}

template<typename T>
unsigned int CustomVector<T>::max_size() const {
    cout << "In max_size()"<<"\n";
    return currCapacity;
}

template<typename T>
bool CustomVector<T>::empty() const {
    cout << "In empty()"<<"\n";
    return size() == 0;
}


template<typename T> 
void CustomVector<T>::reserve(unsigned int cap){
    cout << "In reserve(..)"<<"\n";
    T *newArr;
    try{
        newArr = new T[(sizeof(T)* cap)];
    } catch (const std::bad_alloc& ba){
        cout << "CustomVector reserve(): memory allocation failure: " << ba.what()<<"\n";
    }

    if(buffer != nullptr) {
        for(unsigned int i =0; i< vectSize; i++ ) newArr[i] = buffer[i];
        delete[] buffer;
        buffer = nullptr;
    }
    buffer = newArr;
    currCapacity = cap; 
    
}

template<typename T>
unsigned int CustomVector<T>::capacity() const {
    cout << "In capacity()"<<"\n";
    return currCapacity;
}

template<typename T>
void CustomVector<T>::shrink_to_fit(){
    cout << "In shrink_to_fit()"<<"\n";
    for(auto it = end(); it< begin() + currCapacity; it++) it->~T();
    currCapacity = vectSize;

}


/** Access **/
template <typename T>
T& CustomVector<T>::operator[] (unsigned int idx){
    //cout << "In operator[] (...)"<<"\n";
    return buffer[idx];
}
template <typename T>
T& CustomVector<T>::operator[] (unsigned int idx) const{
    //cout << "In operator[] (...)"<<"\n";
    return buffer[idx];
}

template <typename T>
T& CustomVector<T>::at(unsigned int idx){
    //cout << "In at(...)"<<"\n";
    try{
        return buffer[idx];
    } catch(const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << "\n";
    }
    
}

template <typename T>
T& CustomVector<T>::at(unsigned int idx) const{
    //cout << "In at(...)"<<"\n";
    try{
        return buffer[idx];
    } catch(const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << "\n";
    }
    
}

template <typename T>
T& CustomVector<T>::front() const{
    cout << "In front()"<<"\n";
    return buffer[0];
}

template <typename T>
T& CustomVector<T>::back() const{
    cout << "In back()"<<"\n";
    return buffer[vectSize-1];
}

template <typename T>
T* CustomVector<T>::data() const{
    cout << "In data()"<<"\n";
    return buffer;
}


/** Modifiers **/
template<typename T>
void CustomVector<T>::clear(){
    cout << "In clear()"<<"\n";
    if(buffer != nullptr) delete[] buffer;
    buffer = nullptr;
    vectSize = 0;
}

template<typename T>
void CustomVector<T>::assign(unsigned int count, const T &item){
    cout << "In assign(...)"<<"\n";
    resize(count);
    this->vectSize = count;
    for(int i = 0; i < count; i++) this->at(i) = item;
}

template<typename T>
void CustomVector<T>::push_back(const T &item){
    cout << "In push_back(...)"<<"\n";
    if(vectSize  == currCapacity){

        if(currCapacity == 0) reserve(1);
        else reserve(2 *currCapacity);
        
    }
    buffer[vectSize++] = item;
}



template<typename T>
void CustomVector<T>::push_front(const T &item){
    cout << "In push_front(...)"<<"\n";
    if(vectSize == currCapacity){
        if(currCapacity == 0) reserve(1);
        else reserve(2 * currCapacity);
    }
    for(unsigned int i = vectSize; i>=1; i--) buffer[i] = buffer[i -1];
    buffer[0] = item;
    ++vectSize;
    
}

template<typename T>
void CustomVector<T>::pop_back(){
    cout << "In pop_back()"<<"\n";
    --vectSize;
    (end()-1)->~T();
}

template<typename T>
void CustomVector<T>::insert(CustomVector<T>::iterator it, const T &item){
    cout << "In insert(...)"<<"\n";
    *it = item;
}
template<typename T>
void CustomVector<T>::insert(unsigned int pos, const T &item){
    cout << "In insert(...)"<<"\n";
    this->buffer[pos] = item;
}

template<typename T>
void CustomVector<T>::erase(CustomVector<T>::iterator it){
    cout << "In erase(...) #1"<<"\n";
    if(it == end()-1) {
        pop_back();
    } else{
        it->~T();
        for(auto i = it; i < end(); i++){
            if(i +1 < end()) *i = *(i +1);
        }
        --vectSize;
    }
}

template<typename T>
void CustomVector<T>::erase(CustomVector<T>::iterator first, CustomVector<T>::iterator last){
    cout << "In erase(...) #2"<<"\n";
} 

template<typename T>
void CustomVector<T>::resize(unsigned int size)  {
    cout << "In resize(...)"<<"\n";
    T *newArr = new T[size];
    
    int stopIdx = (size > vectSize) ? vectSize: size;
    
    for(unsigned int i = 0; i < stopIdx; i++) newArr[i] = buffer[i];
    if(buffer != nullptr) delete[] buffer;
    buffer = newArr;
    currCapacity = size;
    vectSize = size;
}

template<typename T>
void CustomVector<T>::swap(CustomVector<T> &otherV) noexcept{
    cout << "In swap(...)"<<"\n";
    using std::swap;
    unsigned int i = otherV.size();
    swap(this->vectSize, i);
    swap(this->buffer, otherV.buffer);
}

















/*********************************** TESTS AND DEBUG ***********************************************/


class Tst
{
private:
    /* data */
    std::string h = "hello";
public:
    Tst() {}
    ~Tst() {}
    friend std::ostream& operator<< (std::ostream &out, const Tst& t){ 
        out << t.h; 
        return out; 
    } 
};



template <typename T>
void printVect(const std::string &msg, const CustomVector<T> &vect){
    cout << msg<<"\n" ;
    cout << "\t[";
    for(int i = 0 ; i< vect.size(); i++){
        cout << vect.at(i) <<",";
    }
    cout << "]\n";
}

int main(int argc, char **argv){
    CustomVector<int> myVect0;
    for(int i = 0; i< 11; i++) myVect0.push_back(i*5 + 20 %3);
    //for(int i = 0; i< 11; i++) myVect0.push_back(Tst());
    printVect("PRINTING myVect0",myVect0);
    CustomVector<int>::iterator it = myVect0.begin();
    //myVect0.insert(it +2, 707);
    myVect0.erase(it +2);
    printVect("PRINTING myVect0",myVect0);
    myVect0.pop_back();
    printVect("PRINTING myVect0",myVect0);
    myVect0.shrink_to_fit();
    printVect("PRINTING myVect0",myVect0);
    myVect0.emplace_back(707);
    printVect("PRINTING myVect0",myVect0);
    cout << "DONE: Creating 'myVect0' with constructor 'CustomVector()'\n";



    /*
    void erase(iterator first, iterator last);
    */

}
