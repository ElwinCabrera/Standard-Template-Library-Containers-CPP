#include <iostream>
#include <cassert>
#include <string>
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




void string_testConstructorDestructorsAssign(){

}

void string_testElementAccess(){

}

void string_operators(){

}

void string_testIterators(){

}

void string_testInsert(){
    BasicString s("xmplr");
    //BasicString s("Exmplr");
 
    // insert(size_type index, size_type count, char ch)
    s.insert((unsigned)0, (unsigned)1, 'E');
    printVect("1) ", s);
    assert("Exmplr" == s);
 
    // insert(size_type index, const char* s)
    s.insert(2, "e");
    printVect("2) ", s);
    assert("Exemplr" == s);
    
 
    // insert(size_type index, string const& str)
    s.insert(6, "a");
    assert("Exemplar" == s);
    printVect("3) ", s);
 
    // insert(size_type index, string const& str,
    //     size_type index_str, size_type count)
    s.insert(8, " is an example string.", 0, 14);
    printVect("4) ", s);
    assert("Exemplar is an example" == s);
    
    // insert(const_iterator pos, char ch)
    //s.insert(s.cbegin() + s.find_first_of('n') + 1, ':');
    auto it = s.begin();
    s.insert(s.begin()+14, ':');
    printVect("5) ", s);
    assert("Exemplar is an: example" == s);
 
    // insert(const_iterator pos, size_type count, char ch)
    //s.insert(s.cbegin() + s.find_first_of(':') + 1, 2, '=');
    s.insert(s.begin()  + 14, 2, '=');
    printVect("6) ", s);
    //assert("Exemplar is an:== example" == s);
 
    // insert(const_iterator pos, InputIt first, InputIt last)
}

void string_testErase(){
    
}

void string_testAppend(){
    BasicString s1("string");
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

void string_testCompare(){
    // 1) Compare with other string
    {  
        BasicString s1("Batman");
        BasicString s2("Superman"); 
        
        int compare_value{ s1.compare(s2)   };
        std::cout << (
            compare_value < 0 ? "Batman comes before Superman\n" :
            compare_value > 0 ? "Superman comes before Batman\n" :
            "Superman and Batman are the same.\n"
        );
    }
 
    // 2) Compare substring with other string
    {
        BasicString s1("Batman");
        BasicString s2("Superman");
        int compare_value{s1.compare(3, 3, s2)};
        std::cout << (
            compare_value < 0 ? "man comes before Superman\n" :
            compare_value > 0 ? "Superman comes before man\n" :
            "man and Superman are the same.\n"
        );
    }
 
    // 3) Compare substring with other substring
    {
        
        BasicString s1("Batman");
        BasicString s2("Superman");
 
        int compare_value{s1.compare(3, 3, s2, 5, 3)};
 
        std::cout << (
            compare_value < 0 ? "man comes before man\n" :
            compare_value > 0 ? "man comes before man\n" :
            "man and man are the same.\n"
        );
        // Compare substring with other substring
        // defaulting to end of other string
        //assert(compare_value == s1.compare(3, 3, s2, 5));
    }
 
    // 4) Compare with char pointer
    {
        BasicString s1("Batman");
        int compare_value{s1.compare("Superman")};
 
        std::cout << (
            compare_value < 0 ? "Batman comes before Superman\n" :
            compare_value > 0 ? "Superman comes before Batman\n" :
            "Superman and Batman are the same.\n"
        );
    }
 
    // 5) Compare substring with char pointer
    {
        BasicString s1("Batman");
       
        int compare_value{s1.compare(3, 3, "Superman")};
 
        std::cout << (
            compare_value < 0 ? "man comes before Superman\n" :
            compare_value > 0 ? "Superman comes before man\n" :
            "man and Superman are the same.\n"
        );
    }
 
    // 6) Compare substring with char pointer substring
    {
        BasicString s1("Batman");
        int compare_value{s1.compare(0, 3, "Superman", 5)};
 
        std::cout << (
            compare_value < 0 ? "Bat comes before Super\n" :
            compare_value > 0 ? "Super comes before Bat\n" :
            "Super and Bat are the same.\n"
        );
    }
}

void string_testEndsStartsWith(){
    
}

void string_testReplace(){
    
}

void string_substr(){
    
}

void string_copy(){
    
}

void string_resize(){
    
}




int main(int argc, char **argv){
    string_testInsert();
    string_testCompare();
    return 0;
}