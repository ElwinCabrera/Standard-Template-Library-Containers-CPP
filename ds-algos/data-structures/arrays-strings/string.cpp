#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <string>
#include <climits>
using std::string;
using std::cout;
using std::endl;

class BasicString{
public:

    typedef BasicString String;
    typedef char* iterator;

    BasicString(): buffer(nullptr), bufferSize(0), bufferCap(0) {}
    BasicString(const char c, unsigned int count);
    BasicString(const BasicString &other); //Copy Constructor
    BasicString(const BasicString &&other); //Move constructor
    ~BasicString();
    BasicString& operator=(const BasicString &str);
    BasicString& operator=(BasicString &&other);
    void assign(unsigned int count, const char &c);


    char at(unsigned int idx);
    char operator[](unsigned int idx);
    char front() const   { return buffer[0]; }
    char back() const    { return buffer[bufferSize-1]; }
    char* data() const   { return buffer; }
    char* c_str() const  { return buffer; }


    iterator begin() const { return buffer; }
    iterator end() const   { return buffer + bufferSize; }


    bool empty() const { return bufferSize == 0; }
    unsigned int size() const { return bufferSize; }
    unsigned int max_size() const { return UINT_MAX; }
    void reserve(unsigned int cap);
    unsigned int capacity() const { return bufferCap; }
    void shrinkToFit();

    void clear();
    BasicString& insert(unsigned int idx, unsigned int count, const char c); // Inserts count copies of character ch at the position index
    BasicString& insert(unsigned int idx, const char* string); // Inserts null-terminated character string pointed to by s at the position index. The length of the string is determined by the first null character using Traits::length(s). 
    BasicString& insert(unsigned int idx, const char* string, unsigned int endPos); //Inserts the characters in the range [s, s+count) at the position index. The range can contain null characters.
    BasicString& insert(unsigned int idx , const BasicString &str); //Inserts string str at the position index
    BasicString& insert(unsigned int idx, const BasicString &str, unsigned int index_str, unsigned int count); // Inserts a string, obtained by str.substr(index_str, count) at the position index
    iterator insert(iterator pos, char c); // Inserts character ch before the character pointed by pos
    void insert(iterator pos, unsigned int count, char c); // Inserts count copies of character ch before the element (if any) pointed by pos
    BasicString& erase(unsigned int idx , unsigned int count ); //Removes min(count, size() - index) characters starting at index.
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last); // Removes the characters in the range [first, last).
    void push_back(char c);
    void pop_back();
    BasicString& append(unsigned int count, char c); //Appends count copies of character ch
    BasicString& append(const BasicString &str); // Appends string str
    BasicString& append(const BasicString &str, unsigned int pos, unsigned int count); // Appends a substring [pos, pos+count) of str. If the requested substring lasts past the end of the string, or if count == npos, the appended substring is [pos, size()). If pos > str.size(), std::out_of_range is thrown. 
    BasicString& append(const char* s, unsigned int count); // Appends characters in the range [s, s + count). This range can contain null characters.
    BasicString& append(const char* s); // Appends the null-terminated character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s)
    BasicString& operator+= (const BasicString &str); //Appends string str
    BasicString& operator+= (char c); //Appends character ch
    BasicString& operator+= (const char *s); // Appends the null-terminated character string pointed to by s.
    int compare(const BasicString &str) const; //Compares this string to str.
    int compare(unsigned int pos1, unsigned int count1, const BasicString &str) const; //  Compares a [pos1, pos1+count1) substring of this string to str. If count1 > size() - pos1 the substring is [pos1, size()).
    int compare(unsigned int pos1, unsigned int count1, const BasicString &str, unsigned int pos2, unsigned int count2) const; // Compares a [pos1, pos1+count1) substring of this string to a substring [pos2, pos2+count2) of str. If count1 > size() - pos1 the first substring is [pos1, size()). Likewise, count2 > str.size() - pos2 the second substring is [pos2, str.size()).
    int compare(const char *s) const; //  Compares this string to the null-terminated character sequence beginning at the character pointed to by s with length Traits::length(s).
    int compare(unsigned int pos1, unsigned int count1, const char *s) const; // Compares a [pos1, pos1+count1) substring of this string to the null-terminated character sequence beginning at the character pointed to by s with length Traits::length(s) If count1 > size() - pos1 the substring is [pos1, size()).
    int compare(unsigned int pos1, unsigned int count1, const char *s, unsigned int count2); //  Compares a [pos1, pos1+count1) substring of this string to the characters in the range [s, s + count2). If count1 > size() - pos1 the substring is [pos1, size()). (Note: the characters in the range [s, s + count2) may include null characters.)
    bool startsWith(BasicString &str) const; // a string str. (new in c++20)
    bool startsWith(char c) const noexcept; //a single character c. (new in c++20)
    bool startsWith(const char *s) const; //a null-terminated character string s. (new in c++20)
    bool endsWith(BasicString &str) const; // a string str. (new in c++20)
    bool endsWith(char c) const noexcept; //a single character c. (new in c++20)
    bool endsWith(const char *s) const; //a null-terminated character string s. (new in c++20)

    BasicString substr(unsigned int pos , unsigned int count) const;








private:
    char *buffer;
    unsigned int bufferSize;
    unsigned int bufferCap;
};

