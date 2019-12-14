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
    BasicString h = "hello";
public:
    Tst() {}
    ~Tst() {}
    friend std::ostream& operator<< (std::ostream &out, const Tst& t){ 
        out << t.h; 
        return out; 
    } 
};



template <typename Obj>
void printVect(const BasicString &msg, const Obj &vect){
    cout << msg<<"" ;
    cout << "[";
    for(int i = 0 ; i< vect.size(); i++){
        if(i+1 != vect.size()) cout << vect.at(i) <<",";
        else cout << vect.at(i);
    }
    cout << "] size: " << vect.size()<<"\n";
}




void string_testConstructorDestructorsAssign(){

    {
    // string::string()
    BasicString s;
    assert(s.empty() && (s.size() == 0));
  }
 
  {
    // string::string(size_type count, charT ch)
    BasicString s(4, '=');
    std::cout << s << '\n'; // "===="
  }
 
  {
    BasicString const other("Exemplary");
    // string::string(string const& other, size_type pos, size_type count)
    BasicString s(other, 0, other.size()-1);
    std::cout << s << '\n'; // "Exemplar"
  }
 
  {
    // string::string(charT const* s, size_type count)
    BasicString s("C-style string", 7);
    std::cout << s << '\n'; // "C-style"
  }
 
  {
    // string::string(charT const* s)
    BasicString s("C-style\0string");
    std::cout << s << '\n'; // "C-style"
  }
 
  {
    char mutable_c_str[] = "another C-style string";
    // string::string(InputIt first, InputIt last)
    BasicString s(std::begin(mutable_c_str)+8, std::end(mutable_c_str)-1);
    std::cout << s << '\n'; // "C-style string"
  }
 
  {
    BasicString const other("Exemplar");
    BasicString s(other);
    std::cout << s << '\n'; // "Exemplar"
  }
 
  {
    // string::string(string&& str)
    BasicString s(BasicString("C++ by ") + BasicString("example"));
    std::cout << s << '\n'; // "C++ by example"
  }
 
//   {
//     // string(std::initializer_list<charT> ilist)
//     BasicString s({ 'C', '-', 's', 't', 'y', 'l', 'e' });
//     std::cout << s << '\n'; // "C-style"
//   }
 
  {
    // overload resolution selects string(InputIt first, InputIt last) [with InputIt = int]
    // which behaves as if string(size_type count, charT ch) is called
    BasicString s(3, 'A');
    std::cout << s << '\n'; // "AAA"
  }

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
    BasicString s("This is an example");
    std::cout << s << '\n';
 
    s.erase(0, 5); // Erase "This "
    std::cout << s << '\n';
 
    s.erase(std::find(s.begin(), s.end(), ' ')); // Erase ' '
    std::cout << s << '\n';

    
    s.erase(s.begin()+2, s.begin()+4); // erase 'an'
    std::cout << s << '\n';

    //s.erase(s.find(' ')); // Trim from ' ' to the end of the string
    s.erase(2); // Trim from ' ' to the end of the string
    std::cout << s << '\n';
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
     BasicString a = "0123456789abcdefghij";
 
    // count is npos, returns [pos, size())
    BasicString sub1 = a.substr(10);
    std::cout << sub1 << '\n';
 
    // both pos and pos+count are within bounds, returns [pos, pos+count)
    BasicString sub2 = a.substr(5, 3);
    std::cout << sub2 << '\n';
 
    // pos is within bounds, pos+count is not, returns [pos, size()) 
    BasicString sub4 = a.substr(a.size()-3, 50);
    std::cout << sub4 << '\n';
 
    try {
        // pos is out of bounds, throws
        BasicString sub5 = a.substr(a.size()+3, 50);
        std::cout << sub5 << '\n';
    } catch(const std::out_of_range& e) {
        std::cout << "pos exceeds string size\n";
    }
}

void string_copy(){
    BasicString foo("quuuux");
    char bar[7]{};
    foo.copy(bar, sizeof(bar));
    std::cout << bar << '\n';
}

void string_resize(){
    std::cout << "Basic functionality:\n";
    const unsigned  desired_length(8);
    BasicString     long_string( "Where is the end?" );
    BasicString     short_string( "Ha" );
 
    // Shorten
    std::cout << "Before: \"" << long_string << "\" Size: " <<long_string.size()<<"\n";
    long_string.resize( desired_length );
    std::cout << "After: \"" << long_string <<  "\" Size: " <<long_string.size()<<"\n";
 
    // Lengthen
    std::cout << "Before: \"" << short_string <<  "\" Size: " <<short_string.size()<<"\n";
    short_string.resize( desired_length, 'a' );
    std::cout << "After: \"" << short_string <<  "\" Size: " <<short_string.size()<<"\n";
 
    std::cout  << "\nErrors:\n";
    {
        BasicString s;    
 
        try {
            // size is OK, no length_error
            // (may throw bad_alloc)
            //s.resize(s.max_size() - 1, 'x');
        } catch (const std::bad_alloc&) {
            std::cout << "1. bad alloc\n";
        }
 
        try {
            // size is OK, no length_error
            // (may throw bad_alloc)
            //s.resize(s.max_size(), 'x');
        } catch (const std::bad_alloc& exc) {
            std::cout << "2. bad alloc\n";
        }
 
        try {
            // size is BAD, throw length_error
            s.resize(s.max_size() + 1, 'x');
        } catch (const std::length_error&) {
            std::cout << "3. length error\n";
        }
     }
}




int main(int argc, char **argv){
    string_testInsert();
    std::cout<<"\n";
    string_testCompare();
    std::cout<<"\n";
    string_testErase();
    std::cout<<"\n";
    string_copy();
    std::cout<<"\n";
    string_substr();
    std::cout<<"\n";
    string_resize();
    std::cout<<"\n";
    string_testConstructorDestructorsAssign();
    return 0;
}