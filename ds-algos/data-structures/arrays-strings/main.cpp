#include <iostream>
//#include "my-vector.cpp"
#include "my-string.cpp"

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



template <typename Obj>
void printVect(const std::string &msg, const Obj &vect){
    cout << msg<<"" ;
    cout << "[";
    for(int i = 0 ; i< vect.size(); i++){
        if(i+1 != vect.size()) cout << vect.at(i) <<",";
        else cout << vect.at(i);
    }
    cout << "] size: " << vect.size()<<"\n";
}

int main(int argc, char **argv){
    BasicString s1("string");
    BasicString s2 = s1;

    
    const char* cptr = "C-string";
    const char carr[] = "Two and one";
 
    BasicString output;
 
    // 1) Append a char 3 times. 
    // Notice, this is the only overload accepting chars.
    output.append(3, '*');
    printVect("1) ", output);
 
    //  2) Append a whole string
    output.append(s1);
    printVect("2) ", output);
 
    // 3) Append part of a string (last 3 letters, in this case)
    output.append(s1, 3, 3);
    printVect("3) ", output);
 
    // 4) Append part of a C-string
    // Notice, because `append` returns *this, we can chain calls together
    output.append(1, ' ').append(carr, 4);
    printVect("4) ", output);
 
    // 5) Append a whole C-string
    output.append(cptr);
    printVect("5) ", output);
 
    // 6) Append range
    //output.append(&carr[3], std::end(carr));
    //printVect("6) ", output);
 
    // 7) Append initializer list
    //output.append({ ' ', 'l', 'i', 's', 't' });
    //printVect("7) ", output);

}