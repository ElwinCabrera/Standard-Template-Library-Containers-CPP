#include <iostream>
#include "my-vector.cpp"

using std::cout;
using std::endl;

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
void printVect(const std::string &msg, const T &vect){
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
    printVect("Printing 'myVect0'",myVect0);
    myVect0.erase(myVect0.begin()+1,myVect0.begin()+4);
    printVect("Printing 'myVect0'",myVect0);
    cout << "DONE: Creating 'myVect0' with constructor 'CustomVector()'\n";
}