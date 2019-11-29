
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
    int vectCapacity;
    int vectSize;

    T *vectArray;
public:
    CustomVector();
    T& operator[](int idx);
     void push_back(const T &item);

};

template<typename T>
void CustomVector<T>::push_back(const T &elem){

}