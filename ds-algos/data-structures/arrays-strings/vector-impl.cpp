
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

template<class T>
class CustomVector{
    
private:
    unsigned int currCapacity;
    unsigned int vectSize;

    T *vectArray;
public:
    typedef typename T *iterator;
    CustomVector();
    CustomVector(unsigned int size);
    CustomVector(unsigned int size, const T &type);
    CustomVector(const CustomVector<T> &v);
    ~CustomVector();
    CustomVector<T>& operator=(const CustomVector<T> &v);

    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();
    iterator cbegin() const;
    iterator cend() const;
    iterator crbegin() const;
    iterator crend() const;


    
    unsigned int size() const;
    unsigned int max_size() const;
    void resize();
    unsigned int capacity() const;
    bool empty() const;
    void reserve(int cap, bool copyOrig);
    void shrink_to_fit();

    T& operator[](unsigned int idx);
    T& at(unsigned int idx);
    T& front() const;
    T& back() const;
    T* data() const;

    void assign(unsigned int count, const T &value);
    void push_back(const T &item);
    void push_front(const T &item);
    void pop_back();
    void insert(unsigned int pos, const T &item);
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    void swap(CustomVector<T> &otherV);
    void clear();
    //void emplace();
    //void emplace_back();

    //void get_allocator
    

    
    


};


/** Constructors and Destructors **/
template<typename T>
CustomVector<T>::CustomVector(){
    currCapacity = 0;
    vectSize = 0;
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size){
    reserve(size, false);
}

template<typename T>
CustomVector<T>::CustomVector(unsigned int size, const T &item){
    reserve(size, false);
    for(int i = 0; i < vectSize; i++) vectArray[i] = item;
}

template<typename T>
CustomVector<T>::CustomVector(const CustomVector<T> &v){
    reserve(v.size(), false);
    for(int i = 0; i < vectSize; i++) vectArray[i] = v.at(i);
}

template<typename T>
CustomVector<T>::~CustomVector(){
    delete[] vectArray;
}

template<typename T>
CustomVector<T>& CustomVector<T>::operator=(const CustomVector<T> &v){

}


/** Iterators **/
template<typename T>
CustomVector<T>::iterator CustomVector<T>::begin(){

}

template<typename T>
CustomVector<T>::iterator CustomVector<T>::end(){
    
}

template<typename T>
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
    
}


/** Capacity Functions **/
template<typename T>
unsigned int CustomVector<T>::size() const {
    return vectSize;
}

template<typename T>
unsigned int CustomVector<T>::max_size() const {
    return currCapacity;
}

template<typename T> 
void CustomVector<T>::reserve(int cap, bool copyOrig){

    T *newArr = new T[cap];
    if(newArr == nullptr) throw memoryAllocationError("CustomVector reserve(): memory allocation failure");

    if(copyOrig){
        for(int i =0; i< vectSize; i++ ) newArr[i] = vectArray[i];
    }

    if(vectArray != nullptr) delete[] vectArray;
    vectArray = newArr;
    currCapacity = cap; 
}

template<typename T>
unsigned int CustomVector<T>::capacity() const {
    return currCapacity;
}

template<typename T>
void CustomVector<T>::shrink_to_fit(){
    
}


/** Access **/
template <typename T>
T& CustomVector<T>::operator[] (unsigned int i){
    return vectArray[i];
}

template <typename T>
T& CustomVector<T>::at(unsigned int i){
    return vectArray[i];
}

template <typename T>
T& CustomVector<T>::front() const{
    return vectArray[0];
}

template <typename T>
T& CustomVector<T>::back() const{
    return vectArray[vectSize-1];
}

template <typename T>
T* CustomVector<T>::data() const{
    return vectArray;
}


/** Modifiers **/
template<typename T>
void CustomVector<T>::assign(unsigned int count, const T &item){

}

template<typename T>
void CustomVector<T>::push_back(const T &item){
    if(vectSize  == currCapacity){

        if(currCapacity == 0) reserve(1, false);
        else {
            reserve(2 *currCapacity, true);
        }
    }
    vectArray[vectSize++] = item;
}

template<typename T>
void CustomVector<T>::push_front(const T &item){
    
}

template<typename T>
void CustomVector<T>::pop_back(){
    
}

template<typename T>
void CustomVector<T>::insert(unsigned int pos, const T &item){

}

template<typename T>
void CustomVector<T>::erase(CustomVector<T>::iterator it){
    
}

template<typename T>
void CustomVector<T>::erase(CustomVector<T>::iterator first, CustomVector<T>::iterator last){
    
}

template<typename T>
void CustomVector<T>::swap(CustomVector<T> &otherV){
    
}