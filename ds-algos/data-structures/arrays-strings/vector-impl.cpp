
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
    vectArray = nullptr;
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
CustomVector<T>::CustomVector( const CustomVector<T> &v){
    reserve(v.size());
    for(int i = 0; i < v.size(); i++) vectArray[i] = v[i];
    cout << "In Copy Constructor #4"<<"\n";
}

template<typename T>
CustomVector<T>::CustomVector(CustomVector<T> &&other) noexcept {
    cout << "In Move Constructor #5"<<"\n";
}

template<typename T>
CustomVector<T>::~CustomVector(){
    if(vectArray != nullptr) delete[] vectArray;
    cout << "In Destructor "<<"\n";
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
    cout << "In begin()"<<"\n";
    return vectArray;
}

template<typename T>
typename CustomVector<T>::iterator CustomVector<T>::end(){
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
    T *newArr;
    try{
        newArr = new T[(sizeof(T)* cap)];
    } catch (const std::bad_alloc& ba){
        cout << "CustomVector reserve(): memory allocation failure: " << ba.what()<<"\n";
    }

    if(vectArray != nullptr) {
        for(unsigned int i =0; i< vectSize; i++ ) newArr[i] = vectArray[i];
        delete[] vectArray;
    }
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
    using std::swap;

    swap(vectArray, otherV.vectArray);
}

template<typename T>
void CustomVector<T>::swap(CustomVector<T> &otherV){
    cout << "In swap(...)"<<"\n";
    CustomVector<T> tmp(otherV);
    otherV = vectArray;
    vectArray = tmp;
}











template <typename T>
void printVect(CustomVector<T> &vect){
    cout << "PRINTING VECTOR...\n";
    cout << "\t[";
    for(int i = 0 ; i< vect.size(); i++){
        cout << vect[i] <<",";
    }
    cout << "]\n";
}

int main(int argc, char **argv){
    CustomVector<int> myVect0;
    myVect0.push_back(1);
    myVect0.push_back(2);
    myVect0.push_back(3);
    //printVect(myVect0);
    cout << "DONE: Creating 'myVect0' with constructor 'CustomVector()'\n";
    
    //CustomVector<int> myVect1(3);
    //printVect(myVect1);
   // cout << "DONE: Creating 'myVect1' with constructor 'CustomVector(unsigned int cap)'\n";

    //CustomVector<int> myVect2(3,0);
    //printVect(myVect2);
    //cout << "DONE: Creating 'myVect2' with constructor 'CustomVector(unsigned int cap, T &value)'\n";

}


    /*CustomVector(); // -- DONE
    CustomVector(unsigned int size); // -- DONE
    CustomVector(unsigned int size, const T &type); // -- DONE
    CustomVector(const CustomVector<T> &v); // -- DONE
    ~CustomVector(); // -- DONE
    CustomVector<T>& operator=(const CustomVector<T> &v); // -- DONE

    iterator begin(); // -- DONE
    iterator end(); // -- DONE

    unsigned int size() const; // -- DONE
    unsigned int max_size() const; // -- DONE
    void resize();// -- DONE
    unsigned int capacity() const; // -- DONE
    bool empty() const; // -- DONE
    void reserve(unsigned int cap);// -- DONE
    void shrink_to_fit();

    T& operator[](unsigned int idx); // -- DONE
    T& at(unsigned int idx); // -- DONE
    T& front() const; // -- DONE
    T& back() const; // -- DONE
    T* data() const;

    void assign(unsigned int count, const T &value);
    void push_back(const T &item); // -- DONE
    void push_front(const T &item); // -- DONE
    void pop_back();// -- DONE
    void insert(unsigned int pos, const T &item);
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    void resize(unsigned int size);// -- DONE
    void swap(CustomVector<T> &otherV); // -- DONE
    void clear(); // -- DONE
    */