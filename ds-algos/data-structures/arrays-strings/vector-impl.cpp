
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
using std::cout;
using std::endl;

template<class T>
class CustomVector{
    
private:
    unsigned int currCapacity;
    unsigned int vectSize;

    T *vectArray;
public:
    typedef typename T *iterator;
    CustomVector();//
    CustomVector(unsigned int size);//
    CustomVector(unsigned int size, const T &type);//
    CustomVector(const CustomVector<T> &v);//
    ~CustomVector();//
    CustomVector<T>& operator=(const CustomVector<T> &v);//

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
    T& at(unsigned int idx);//
    T& front() const;//
    T& back() const;//
    T* data() const;

    void assign(unsigned int count, const T &value);
    void push_back(const T &item);//
    void push_front(const T &item);//
    void pop_back();//
    void insert(unsigned int pos, const T &item);
    void erase(iterator pos);//
    void erase(iterator first, iterator last);
    void resize(unsigned int size);//
    void swap(CustomVector<T> &otherV);
    void clear();//
    //void emplace();
    //void emplace_back();

    //void get_allocator
};


/** Constructors and Destructors **/
template<typename T>
CustomVector<T>::CustomVector(){
    currCapacity = 0;
    vectSize = 0;
    cout << "In Constructor #1"<<"\n";
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size){
    reserve(size);
    cout << "In Constructor #2"<<"\n";
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size, const T &item){
    reserve(size);
    for(int i = 0; i < vectSize; i++) vectArray[i] = item;
    cout << "In Constructor #3"<<"\n";
}

template<typename T>
CustomVector<T>::CustomVector(const CustomVector<T> &v){
    reserve(v.size());
    for(int i = 0; i < vectSize; i++) vectArray[i] = v[i];
    cout << "In Constructor #4"<<"\n";
}

template<typename T>
CustomVector<T>::~CustomVector(){
    delete[] vectArray;
    cout << "In Destructor "<<"\n";
}

template<typename T>
CustomVector<T>& CustomVector<T>::operator=(const CustomVector<T> &v){
    cout << "In operator= (...)"<<"\n";
    resize(v.size());
    for(int i = 0; i< vectSize; i++) vectArray[i] = v[i];
    return *this;
}


/** Iterators **/
template<typename T>
CustomVector<T>::iterator CustomVector<T>::begin(){
    cout << "In begin()"<<"\n";
    return vectArray;
}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::end(){
    cout << "In end()"<<"\n";
    return vectArray + size();
}

/*template<typename T>
CustomVector<T>::iterator CustomVector<T>::rbegin(){

}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::rend(){
    
}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::cbegin() const{

}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::cend() const{
    
}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::crbegin() const {

}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::crend() const{
    
}*/


/** Capacity Functions **/
template<typename T>
unsigned int CustomVector<T>::size() const {
    cout << "In size()"<<"\n";
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

    T *newArr = new T[cap];
    if(newArr == nullptr) throw memoryAllocationError("CustomVector reserve(): memory allocation failure");

    for(unsigned int i =0; i< vectSize; i++ ) newArr[i] = vectArray[i];
    
    if(vectArray != nullptr) delete[] vectArray;
    vectArray = newArr;
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
}


/** Access **/
template <typename T>
T& CustomVector<T>::operator[] (unsigned int idx){
    cout << "In operator[] (...)"<<"\n";
    return vectArray[idx];
}

template <typename T>
T& CustomVector<T>::at(unsigned int idx){
    cout << "In at(...)"<<"\n";
    try{
        return vectArray[idx];
    } catch(const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << "\n";
    }
    
}

template <typename T>
T& CustomVector<T>::front() const{
    cout << "In front()"<<"\n";
    return vectArray[0];
}

template <typename T>
T& CustomVector<T>::back() const{
    cout << "In back()"<<"\n";
    return vectArray[vectSize-1];
}

template <typename T>
T* CustomVector<T>::data() const{
    cout << "In data()"<<"\n";
    return vectArray;
}


/** Modifiers **/
template<typename T>
void CustomVector<T>::clear(){
    cout << "In clear()"<<"\n";
    delete[] vectArray;
    currCapacity = 0;
    vectSize = 0;
}

template<typename T>
void CustomVector<T>::assign(unsigned int count, const T &item){
    cout << "In assign(...)"<<"\n";
}

template<typename T>
void CustomVector<T>::push_back(const T &item){
    cout << "In push_back(...)"<<"\n";
    if(vectSize  == currCapacity){

        if(currCapacity == 0) reserve(1);
        else reserve(2 *currCapacity);
        
    }
    vectArray[vectSize++] = item;
}

template<typename T>
void CustomVector<T>::push_front(const T &item){
    cout << "In push_front(...)"<<"\n";
    if(vectSize == currCapacity){
        if(currCapacity == 0) reserve(1);
        else reserve(2 * currCapacity);
    }
    for(unsigned int i = vectSize; i>=1; i--) vectArray[i] = vectArray[i -1];
    vectArray[0] = item;
    ++vectSize;
    
}

template<typename T>
void CustomVector<T>::pop_back(){
    cout << "In pop_back()"<<"\n";
    --vectSize;
}

template<typename T>
void CustomVector<T>::insert(unsigned int pos, const T &item){
    cout << "In insert(...)"<<"\n";
}

template<typename T>
void CustomVector<T>::erase(CustomVector<T>::iterator it){
    cout << "In erase(...) #1"<<"\n";
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
    
    for(unsigned int i = 0; i < stopIdx; i++) newArr[i] = vectArray[i];
    if(vectArray != nullptr) delete[] vectArray;
    vectArray = newArr;
    currCapacity = size;
    vectSize = size;
}

template<typename T>
void CustomVector<T>::swap(CustomVector<T> &otherV){
    cout << "In swap(...)"<<"\n";
    CustomVector<T> tmp(otherV);
    otherV = vectArray;
    vectArray = tmp;
}

template <typename T>
void printVect(CustomVector<T> vect){
    cout << "PRINTING VECTOR...\n";
    cout << "\t[";
    for(T item: vect){
        cout << item <<",";
    }
    cout << "]\n";
}

int main(int argc, char **argv){
    CustomVector<int> myVect;
    
}