#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <math.h>
#include <new>

class BasicString{
public:

    typedef BasicString String;
    typedef char* iterator;
    static const unsigned int npos = -1;

    /*************** Member functions **************/
    BasicString(): buffer(nullptr), bufferSize(0), bufferCap(0) {}
    BasicString(unsigned int count, char c); 
    BasicString(const BasicString &other, unsigned int pos, unsigned int count = npos);
    BasicString(const char *s);
    BasicString(const char *s, unsigned int count);
    BasicString(iterator inputFirst, iterator inputLast);

    BasicString(const char c, unsigned int count);
    BasicString(const BasicString &other); //Copy Constructor
    BasicString(BasicString &&other) noexcept; //Move constructor
    ~BasicString();
    BasicString& operator=(const BasicString &str);
    BasicString& operator=(BasicString &&other);

    void assign(unsigned int count, const char c);
    
    /*************** Operators **************/
    friend bool operator==(const BasicString &s1, const BasicString &s2);
    friend BasicString operator+(const BasicString &s1, const BasicString &s2);
    friend std::ostream& operator<<(std::ostream &os, const BasicString &s);
    friend std::istream& operator>>(std::istream &is, const BasicString &s);


    /*************** Element access **************/
    char at(unsigned int idx);
    char at(unsigned int idx) const;
    char operator[](unsigned int idx) { return buffer[idx]; }
    char front() const   { return buffer[0]; }
    char back() const    { return buffer[bufferSize-1]; }
    char* data() const   { return buffer; }
    char* c_str() const  { return buffer; }



    /*************** Iterators **************/
    iterator begin() const { return buffer; }
    iterator end() const   { return buffer + bufferSize; }



    /*************** Capacity **************/
    bool empty() const { return bufferSize == 0; }
    unsigned int size() const { return bufferSize; }
    unsigned int max_size() const { return UINT_MAX; }
    void reserve(unsigned int cap);
    unsigned int capacity() const { return bufferCap; }
    void shrink_to_fit();



    /*************** Operations **************/
    void clear();
    BasicString& insert(unsigned int idx, unsigned int count, char c); // Inserts count copies of character ch at the position index
    BasicString& insert(unsigned int idx, const char* string); // Inserts null-terminated character string pointed to by s at the position index. The length of the string is determined by the first null character using Traits::length(s). 
    BasicString& insert(unsigned int idx, const char* string, unsigned int endPos); //Inserts the characters in the range [s, s+count) at the position index. The range can contain null characters.
    BasicString& insert(unsigned int idx , const BasicString &str); //Inserts string str at the position index
    BasicString& insert(unsigned int idx, const BasicString &str, unsigned int index_str, unsigned int count = npos); // Inserts a string, obtained by str.substr(index_str, count) at the position index
    iterator insert(iterator pos, char c); // Inserts character ch before the character pointed by pos
    void insert(iterator pos, unsigned int count, char c); // Inserts count copies of character ch before the element (if any) pointed by pos
    BasicString& erase(unsigned int idx , unsigned int count = npos ); //Removes min(count, size() - index) characters starting at index.
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
    bool starts_with(BasicString &str) const; // a string str. (new in c++20)
    bool starts_with(char c) const noexcept; //a single character c. (new in c++20)
    bool starts_with(const char *s) const; //a null-terminated character string s. (new in c++20)
    bool ends_with(BasicString &str) const; // a string str. (new in c++20)
    bool ends_with(char c) const noexcept; //a single character c. (new in c++20)
    bool ends_with(const char *s) const; //a null-terminated character string s. (new in c++20)
    BasicString& replace(unsigned int pos, unsigned int count, const BasicString &str); //string str
    BasicString& replace(const iterator first, const iterator last, const BasicString &str); //string str 
    BasicString& replace(unsigned int pos, unsigned int count, const BasicString &str, unsigned int pos2, unsigned int count2);  // substring [pos2, pos2 + count2) of str, except if count2==npos or if would extend past str.size(), [pos2, str.size()) is used.
    BasicString& replace(unsigned int pos, unsigned int count, const char *cstr, unsigned int count2); // characters in the range [cstr, cstr + count2);
    BasicString& replace(const iterator first, const iterator last, const char *cstr, unsigned int count2); // characters in the range [cstr, cstr + count2);
    BasicString& replace(unsigned int pos, unsigned int count, const char *cstr); // characters in the range [cstr, cstr + Traits::length(cstr));
    BasicString& replace(const iterator first, const iterator last, const char *cstr); // characters in the range [cstr, cstr + Traits::length(cstr));
    BasicString& replace(unsigned int pos, unsigned int count, unsigned int count2, char c); // count2 copies of character ch;
    BasicString& replace(const iterator first, const iterator last, unsigned int count2, char c); // count2 copies of character ch;
    BasicString substr(unsigned int pos =0, unsigned int count= npos) const; // Returns a substring [pos, pos+count). If the requested substring extends past the end of the string, or if count == npos, the returned substring is [pos, size()). 
    unsigned int copy(char *dest, unsigned int count, unsigned int pos = 0) const; // Copies a substring [pos, pos+count) to character string pointed to by dest. If the requested substring lasts past the end of the string, or if count == npos, the copied substring is [pos, size()). The resulting character string is not null-terminated. 
    /*
    Resizes the string to contain count characters.
    If the current size is less than count, additional characters are appended.
    If the current size is greater than count, the string is reduced to its first count elements.
    The first version initializes new characters to CharT(), the second version initializes new characters to ch. 
    */
    void resize(unsigned int count);
    void resize(unsigned int count, char c);
    //void swap(BasicString &other);
    void swap(BasicString &other) noexcept;




    /*************** Search **************/
    unsigned int find(const BasicString &str, unsigned int pos = 0) const; //Finds the first substring equal to str.
    unsigned int find(const char *s, unsigned int pos , unsigned int count) const; // Finds the first substring equal to the range [s, s+count). This range may contain null characters.
    unsigned int find(const char *s, unsigned int pos = 0) const; // Finds the first substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int find(char c, unsigned int pos = 0) const; // Finds the first character ch (treated as a single-character substring by the formal rules below).
    unsigned int rfind(const BasicString &str, unsigned int pos = npos ) const; // Finds the last substring equal to str.
    unsigned int rfind(const char *s, unsigned int pos , unsigned int count) const; // Finds the last substring equal to the range [s, s+count). This range can include null characters. 
    unsigned int rfind(const char *s, unsigned int pos = npos) const; // Finds the last substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int rfind(char c, unsigned int pos = npos) const; //  Finds the last character equal to ch.
    unsigned int find_first_of(const BasicString &str, unsigned int pos = 0) const; //Finds the first character equal to one of the characters in str.
    unsigned int find_first_of(const char *s, unsigned int pos , unsigned int count) const; // Finds the first character equal to one of the characters in the range [s, s+count). This range can include null characters.
    unsigned int find_first_of(const char *s, unsigned int pos = 0) const; // Finds the first character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int find_first_of(char c, unsigned int pos = 0) const; // Finds the first character equal to ch.
    unsigned int find_first_not_of(const BasicString &str, unsigned int pos = 0) const; //Finds the first character equal to none of characters in str. 
    unsigned int find_first_not_of(const char *s, unsigned int pos , unsigned int count) const; //  Finds the first character equal to none of characters in range [s, s+count). This range can include null characters.
    unsigned int find_first_not_of(const char *s, unsigned int pos = 0) const; // Finds the first character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    unsigned int find_first_not_of(char c, unsigned int pos = 0) const; // Finds the first character equal to ch.
    unsigned int find_last_of(const BasicString &str, unsigned int pos = npos) const; //Finds the last character equal to one of the characters in str.
    unsigned int find_last_of(const char *s, unsigned int pos , unsigned int count) const; // Finds the last character equal to one of the characters in the range [s, s+count). This range can include null characters.
    unsigned int find_last_of(const char *s, unsigned int pos = npos) const; // Finds the last character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int find_last_of(char c, unsigned int pos = npos) const; // Finds the last character equal to ch.
    unsigned int find_last_not_of(const BasicString &str, unsigned int pos ) const; //Finds the last character equal to none of characters in str. 
    unsigned int find_last_not_of(const char *s, unsigned int pos , unsigned int count) const; //  Finds the last character equal to none of characters in range [s, s+count). This range can include null characters.
    unsigned int find_last_not_of(const char *s, unsigned int pos ) const; // Finds the last character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    unsigned int find_last_not_of(char c, unsigned int pos ) const; // Finds the last character equal to ch.

    //operator+ ? 




private:
    char *buffer;
    unsigned int bufferSize;
    unsigned int bufferCap;
};



/*************** Member functions **************/

BasicString::BasicString(unsigned int count, char c): buffer(nullptr), bufferSize(count), bufferCap(0){
    this->reserve(count+1);
    for(unsigned int i = 0; i < this->size(); ++i) this->buffer[i] = c;
}

BasicString::BasicString(const BasicString &other, unsigned int pos, unsigned int count )
: buffer(nullptr), bufferSize(0), bufferCap(0){
    if(pos > other.size()) throw std::out_of_range("in  'BasicString(const BasicString &other, unsigned int pos, unsigned int count )' pos is out of range");
    if(count == npos || pos+ count > other.size()) count = other.size() - pos;
    this->bufferSize = count;
    this->reserve(count+1);
    for(unsigned int i = 0; i < this->size(); ++i) this->buffer[i] = other.at(pos++);
}

BasicString::BasicString(const char *s)
: buffer(nullptr), bufferSize(0), bufferCap(0){
    
    for(unsigned i = 0; s[i] != '\0'; ++i) this->push_back(s[i]);
    this->push_back('\0');
    --this->bufferSize;
    
}

BasicString::BasicString(const char *s, unsigned int count)
: buffer(nullptr), bufferSize(count), bufferCap(0){
    this->reserve(count+1);
    for(unsigned int i = 0; s[i] != '\0' && i < count; ++i) this->buffer[i] = s[i]; 
}
    

BasicString::BasicString(iterator inputFirst, iterator inputLast)
: buffer(nullptr), bufferSize(inputLast - inputFirst), bufferCap(0){
    this->reserve(inputLast - inputFirst + 1);
    for(unsigned int i = 0; i < this->size() && inputFirst != inputLast; ++i) this->buffer[i] = *(inputFirst++);
}
BasicString::BasicString(const char c, unsigned int count)
: buffer(nullptr), bufferSize(count), bufferCap(0){
    this->reserve(count+1);
    for(unsigned int i = 0; i < count; ++i) this->buffer[i] = c;
}

BasicString::BasicString(const BasicString &other): buffer(nullptr), bufferSize(other.size()), bufferCap(0){
    //Copy Constructor
    this->reserve(other.size()+1);
    for(unsigned int i = 0; i < other.size(); ++i) this->buffer[i] = other.buffer[i];
    this->buffer[other.size()] = '\0';   
}
BasicString::BasicString(BasicString &&other) noexcept{ 
    //Move constructor
    this->buffer = other.buffer;
    other.buffer = nullptr;
}
BasicString::~BasicString() {
    if(buffer != nullptr){
        delete [] this->buffer;
        this->buffer = nullptr;
        this->bufferSize = 0;
        this->bufferCap = 0;
    }
}
BasicString& BasicString::operator=(const BasicString &str){
    BasicString tmpStr(str);
    tmpStr.swap(*this);
    return *this;
}
BasicString& BasicString::operator=(BasicString &&other){ }

void BasicString::assign(unsigned int count, const char c){
    resize(count);
    for(unsigned int i = 0; i < count; ++i) this->buffer[i] = c;
}

/*************** Operators **************/
bool operator==(const BasicString &s1, const BasicString &s2){
    if(s1.size() == s2.size()){
        for(unsigned int i = 0; i < s1.size(); ++i) if(s1.at(i) != s2.at(i)) return false;
    } else return false;
    
    return true;
}
BasicString operator+(const BasicString &s1, const BasicString &s2){
    BasicString result(s1);
    result.append(s2);
    return result;
}
std::ostream& operator<<(std::ostream &os, const BasicString &s){
    os << s.data();
    return os;
}
std::istream& operator>>(std::istream &is, const BasicString &s){

}

/*************** Element access **************/
char BasicString::at(unsigned int idx){
    try{
        return this->buffer[idx];
    } catch(const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << "\n";
    }
}

char BasicString::at(unsigned int idx) const{
    try{
        return this->buffer[idx];
    } catch(const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << "\n";
    }
}



/*************** Capacity **************/
void BasicString::reserve(unsigned int cap) {
    if(cap > this->max_size()) throw std::length_error("'resize()' error capacity is more than max size");
    char *newBuffer;
    try{
        newBuffer = new char[(sizeof(char)* cap)];
        for(unsigned int i = 0; i < cap; ++i) newBuffer[i] = '\0';
    } catch (const std::bad_alloc& ba){
        std::cerr << "BasicString reserve(): memory allocation failure: " << ba.what()<<"\n";
    }

    if(buffer != nullptr){
        for(unsigned int i = 0 ; i < this->bufferSize; ++i) newBuffer[i] = this->buffer[i];
        delete[] this->buffer;
        this->buffer = nullptr;
    }
    this->buffer = newBuffer;
    this->bufferCap = cap;
}

void BasicString::shrink_to_fit() {
    for(auto it = this->end(); it< this->begin() + bufferCap; ++it) {
        *it = '\0';
        it = nullptr;
    }
    bufferCap = bufferSize;
}

/*************** Operations **************/
void BasicString::clear() {
    if(this->buffer != nullptr) delete[] this->buffer;
    this->buffer = nullptr;
    this->bufferCap = 0;
    this->bufferSize = 0;
}



BasicString& BasicString::insert(unsigned int idx, unsigned int count, char c) {
    // Inserts count copies of character ch at the position index
    if(idx > this->size() || idx == npos) return *this; // throw an error
    resize(this->size() + count);
    unsigned int end = this->size()-1;
    unsigned int prevEnd = end - count; 
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = c;
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const char* s) {
    // Inserts null-terminated character string pointed to by s at the position index. The length of the string is determined by the first null character using Traits::length(s). 
    if(idx > this->size() || idx == npos) return *this; // throw an error
    unsigned int count = 0;
    const char *cptr = s;
    while(*cptr != '\0') {
        cptr++;
        count++;
    }
    resize(this->size() + count);
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd = end - count; 
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    unsigned int sIdx = 0;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = s[sIdx++];
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const char* s, unsigned int count) {
    //Inserts the characters in the range [s, s+count) at the position index. The range can contain null characters.
    if(idx > this->size() || idx == npos) return *this; // throw an error
    resize(this->size() + count);
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd = end - count; 
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }

    unsigned int sIdx = 0;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = s[sIdx++];
    return *this;
}
BasicString& BasicString::insert(unsigned int idx , const BasicString &str) {
    //Inserts string str at the position index
    if(idx > this->size() || idx == npos) return *this; // throw an error
    resize(this->size() + str.size());
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd = end - str.size(); 
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    unsigned int strIdx = 0;
    for(unsigned int i = idx; i < idx + str.size(); ++i) this->buffer[i] = str.at(strIdx++);
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const BasicString &str, unsigned int index_str, unsigned int count) {
    // Inserts a string, obtained by str.substr(index_str, count) at the position index
    if(idx > this->size() || idx == npos) return *this; // throw an error
    resize(this->size() + count);
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd = end - count; 
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    unsigned int strIdx = 0;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = str.at(index_str++);
    
    return *this;
}
BasicString::iterator BasicString::insert(iterator pos, char c){
    // Inserts character c before the character pointed by pos
    if(pos >= this->end() || pos < this->begin()) return pos; // throw an error
    unsigned int idx = pos - this->begin();
    
    resize(this->size() + 1);
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd =  end - 1; 
    
    
    while (prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    this->buffer[idx] = c;
    return &this->buffer[idx];
}
void BasicString::insert(iterator pos, unsigned int count, char c) {
    // Inserts count copies of character ch before the element (if any) pointed by pos
    if(pos >= this->end() || pos < this->begin()) return; // throw an error
    unsigned int idx = pos - this->begin();
    
    resize(this->size() + 1);
    
    unsigned int end = this->size()-1;
    unsigned int prevEnd =  end - 1; 
    
    while(prevEnd >= idx && prevEnd != npos){
        this->buffer[end] = this->buffer[prevEnd];
        --end;
        --prevEnd;
    }
    for(unsigned int i = idx; i < idx +count; ++i) this->buffer[i] = c;
}


BasicString& BasicString::erase(unsigned int idx , unsigned int count ){
    //Removes min(count, size() - index) characters starting at index.
    if(count == npos) count = this->size() - idx;
    count = std::min(count, this->size() - idx);
    unsigned int idxFast = idx + count;
    while(idxFast < this->size()) this->buffer[idx++] = this->buffer[idxFast++];
    
    this->resize(this->bufferSize - count);
     

    return *this;
} 
BasicString::iterator BasicString::erase(iterator pos){
    
    for(auto it = pos; it != this->end(); ++it) {
        if(it + 1 == this->end()) *(it) = '\0';
        else *(it) = *(it+1);
    }
    *(this->end()) = '\0';
    --this->bufferSize;
    return pos;
}
BasicString::iterator BasicString::erase(iterator first, iterator last){
    // Removes the characters in the range [first, last).
    
    iterator result = first;
    while(last != this->end()) *(first++) = *(last++);
    
    while (first != this->end()) *(first++) = '\0';
    
    
    this->bufferSize -= (first - last);
    return result;
    
} 
void BasicString::push_back(char c){
    if(bufferSize  == bufferCap){
        if(bufferCap == 0) reserve(2);
        else reserve(2 *bufferCap);
    }
    buffer[bufferSize++] = c;
}
void BasicString::pop_back(){
    *(this->end()-1) = '\0';
    --this->bufferSize;
}

BasicString& BasicString::append(unsigned int count, char c){
    //Appends count copies of character ch
    for(unsigned int i = 0; i < count; ++i) this->push_back(c);
    return *this;
} 
BasicString& BasicString::append(const BasicString &str){
    // Appends string str
    for(unsigned int i = 0; i < str.size(); ++i) this->push_back(str.at(i));
    return *this;
} 
BasicString& BasicString::append(const BasicString &str, unsigned int pos, unsigned int count){
    // Appends a substring [pos, pos+count) of str. If the requested substring lasts past the end of the string, or if count == npos, the appended substring is [pos, size()). If pos > str.size(), std::out_of_range is thrown. 
    if(pos == BasicString::npos) count = str.size();
    for(unsigned int i = pos; i < pos + count; ++i) this->push_back(str.at(i));
    return *this;
} 
BasicString& BasicString::append(const char* s, unsigned int count){
    // Appends characters in the range [s, s + count). This range can contain null characters.
    for(unsigned int i = 0; i < count; ++i) this->push_back(s[i]);
    return *this;
} 
BasicString& BasicString::append(const char* s){
    // Appends the null-terminated character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s)
    for(unsigned int i = 0; s[i] != '\0'; ++i) this->push_back(s[i]);
    return *this;
} 
BasicString& BasicString::operator+= (const BasicString &str){
    //Appends string str
    for(unsigned int i = 0; i < str.size(); ++i) this->push_back(str.at(i));
    return *this;
} 
BasicString& BasicString::operator+= (char c){
    //Appends character ch
    this->push_back(c);
    return *this;
} 
BasicString& BasicString::operator+= (const char *s){
    // Appends the null-terminated character string pointed to by s.
    for(unsigned int i = 0; s[i] != '\0'; ++i) this->push_back(s[i]);
    return *this;
}

int BasicString::compare(const BasicString &str) const{
    //Compares this string to str.
    
    unsigned int size = std::min(this->size(), str.size());

    for(unsigned int i = 0; i < size; ++i) {
        int diff = this->buffer[i] - str.at(i);
        if(diff < 0 || diff >0) return diff;  
    }

    if(this->size() < str.size()) return -1;
    else if(this->size() > str.size()) return 1;

    return 0;
} 
int BasicString::compare(unsigned int pos1, unsigned int count1, const BasicString &str) const{
    //  Compares a [pos1, pos1+count1) substring of this string to str. If count1 > size() - pos1 the substring is [pos1, size()).
    if(count1 > this->size() - pos1) count1 = this->size() - pos1;
    unsigned int size = std::min(count1, str.size());

    for(unsigned int i = 0; i < size; ++i) {
        int diff = this->buffer[pos1++] - str.at(i);
        if(diff < 0 || diff >0) return diff;  
    }

    if(count1 < str.size()) return -1;
    else if(count1 > str.size()) return 1;
    return 0;
    
} 
int BasicString::compare(unsigned int pos1, unsigned int count1, const BasicString &str, unsigned int pos2, unsigned int count2) const{
    // Compares a [pos1, pos1+count1) substring of this string to a substring [pos2, pos2+count2) of str. If count1 > size() - pos1 the first substring is [pos1, size()). Likewise, count2 > str.size() - pos2 the second substring is [pos2, str.size()).
    if(count1 > this->size() - pos1) count1 = this->size() - pos1;
    while(pos1 < count1 && pos2 < count2){
        int diff = this->buffer[pos1++] - str.at(pos2++);
        if(diff < 0 || diff > 0) return diff;  
    }
    return 0;
} 
int BasicString::compare(const char *s) const{
    //  Compares this string to the null-terminated character sequence beginning at the character pointed to by s with length Traits::length(s).
    unsigned int idx = 0;
    while(s[idx] != '\0' && idx < this->size() ){
        int diff = this->buffer[idx] - s[idx];
        if(diff < 0 || diff >0) return diff;
        ++idx;
    }
    if(idx < this->size() && s[idx] == '\0') return -1;
    else if(idx >= this->size() && s[idx] != '\0') return 1;

    return 0;
} 
int BasicString::compare(unsigned int pos1, unsigned int count1, const char *s) const{
    // Compares a [pos1, pos1+count1) substring of this string to the null-terminated character sequence beginning at the character pointed to by s with length Traits::length(s) If count1 > size() - pos1 the substring is [pos1, size()).
    if(count1 > this->size() - pos1) count1 = this->size() - pos1;
    unsigned int idx = 0;

    while(s[idx] != '\0' && pos1 < count1 ){
        int diff = this->buffer[pos1++] - s[idx++];
        if(diff < 0 || diff >0) return diff;
    }
    if(pos1 < count1 && s[idx] == '\0') return -1;
    else if(pos1 >= count1 && s[idx] != '\0') return 1;
    
    return 0;

} 
int BasicString::compare(unsigned int pos1, unsigned int count1, const char *s, unsigned int count2){
    // Compares a [pos1, pos1+count1) substring of this string to the characters in the range [s, s + count2). If count1 > size() - pos1 the substring is [pos1, size()). (Note: the characters in the range [s, s + count2) may include null characters.)
    if(count1 > this->size() - pos1) count1 = this->size() - pos1;
    unsigned int size = std::min(count1, count2);
    for(unsigned int i = 0; i < size; ++i) {
        int diff = this->buffer[pos1++] - s[i];
        if(diff < 0 || diff >0) return diff;  
    }

    if(count1 < count2) return -1;
    else if(count1 > count2) return 1;
    
    return 0;
} 
bool BasicString::starts_with(BasicString &str) const{
    // a string str. (new in c++20)
    if(this->size() < str.size()) return false;
    for(unsigned int i = 0 ; i < str.size(); ++i) if(this->buffer[i] != str.at(i)) return false;
    return true;
} 
bool BasicString::starts_with(char c) const noexcept{
    //a single character c. (new in c++20)
    return c == this->buffer[0];
} 
bool BasicString::starts_with(const char *s) const{
    //a null-terminated character string s. (new in c++20)
    for(unsigned int i = 0 ; s[i] != '\0'; ++i) {
        if(i > this->bufferSize || this->buffer[i] != s[i]) return false;
    }
    return true;
} 
bool BasicString::ends_with(BasicString &str) const{
    // a string str. (new in c++20)
    if(this->size() < str.size()) return false;
    unsigned int idx1 = this->size() -1;
    for(unsigned int i = str.size()-1; i != npos; --i) if(str.at(i) != this->buffer[idx1--]) return false;
    return true;
} 
bool BasicString::ends_with(char c) const noexcept{
    //a single character c. (new in c++20)
    return this->buffer[this->size()-1] == c;
} 
bool BasicString::ends_with(const char *s) const{
    //a null-terminated character string s. (new in c++20)
    unsigned int count =0;
    for(unsigned int i =0; i < s[i] != '\0'; ++i ) count++;
    if(this->size() < count) return false;
    unsigned int idx1 = this->size()-1;
    for(unsigned int i = count-1; i >=0; --i) if(this->buffer[idx1--] != s[i]) return false;
    return true;
}

BasicString& BasicString::replace(unsigned int pos, unsigned int count, const BasicString &str){
    //string str 
    //count is how many we chars we are replacing, if count is 0 then we are not replacing but inserting at that pos so we can just call insert(pos, str) in that case
    //if pos+ count is more than the this string length then we just append str starting from pos in this string 
    
    if(pos > this->size()) return *this; // not possible should return error
    if(count == 0) return this->insert(pos, str);
    return this->erase(pos, count).insert(pos, str);
    
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const BasicString &str){
    //string str [first, last)
    
    if(first > this->begin()) return *this; // not possible should return error

    //if(first == last) return this->insert(first, last,str);
    this->erase(first, last);
    
    iterator firstIt = first;
    unsigned int end = last - this->begin();
    int charsToEndCount = this->end() - first;
    unsigned int idx = 0;
    
    if(end > this->size()) {
        this->resize(str.size()+(this->size()-charsToEndCount));
        while(idx < str.size()) *(firstIt++) = str.at(idx++);
    } else {
        while(first != last) *(firstIt++) = str.at(idx++);
    } 
    return *this;
}  
BasicString& BasicString::replace(unsigned int pos, unsigned int count, const BasicString &str, unsigned int pos2, unsigned int count2){
    //count the the # of characters to replace [pos, pos+ count) if count is more than this->size() - pos then we replace all characters starting from [pos, this->size())
    // count2 is the # of characters to copy substring [pos2, pos2 + count2) of str, except if count2==npos or if would extend past str.size(), [pos2, str.size()) is used.
    if(count2 > str.size() || count2 == npos) count2 = str.size() - pos2;
    if(count == 0) return this->insert(pos, str, pos2, count2);
    return this->erase(pos, count).insert(pos, str, pos2, count2);
    
    
}  
BasicString& BasicString::replace(unsigned int pos, unsigned int count, const char *cstr, unsigned int count2){
    // characters in the range [cstr, cstr + count2);
    //if(count2 > str.size() || count2 == npos) count2 = str.size() - pos2;
    if(count == 0) return this->insert(pos, cstr, count2);
    this->erase(pos, count).insert(pos,cstr,count2);
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const char *cstr, unsigned int count2){
    // characters in the range [cstr, cstr + count2);
    unsigned int replCount = last - first;
    unsigned int startIdx = first - this->begin();
    if(first == last) return this->insert(startIdx,cstr,count2);
    this->erase(first, last);
    insert(startIdx,cstr,count2);

    unsigned int idx1 = startIdx;
    unsigned int idx2 = 0;

    return *this;

} 
BasicString& BasicString::replace(unsigned int pos, unsigned int count, const char *cstr){
    // characters in the range [cstr, cstr + Traits::length(cstr));
    if(count == 0) return this->insert(pos, cstr);
    return this->erase(pos, count).insert(pos, cstr);;
    
    
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const char *cstr){
    // characters in the range [cstr, cstr + Traits::length(cstr));
    unsigned int count2 = 0;
    while(cstr[count2] != '\0') cstr[count2++];
    return this->replace(first, last, cstr, count2);
} 
BasicString& BasicString::replace(unsigned int pos, unsigned int count, unsigned int count2, char c){ /*************/
    // count2 copies of character ch;
    if(count == 0) return this->insert(pos, count, c);
    return this->erase(pos, count).insert(pos, count2, c);
} 
BasicString& BasicString::replace(const iterator first, const iterator last, unsigned int count2, char c){
    // count2 copies of character ch;
    this->erase(first, last);
    insert(first, count2, c);
    return *this;
} 
BasicString BasicString::substr(unsigned int pos , unsigned int count) const{
    // Returns a substring [pos, pos+count). If the requested substring extends past the end of the string, or if count == npos, the returned substring is [pos, size()).
    if(pos > this->size()) throw std::out_of_range("first argument is not valid out of range in 'substr'");
    if(count == npos || pos + count > this->size()) count = this->size() - pos;
    BasicString resultStr; 
    for(unsigned int i = pos; i < pos + count; ++i) resultStr.push_back(this->buffer[i]);
    return resultStr;
} 

unsigned int BasicString::copy(char *dest, unsigned int count, unsigned int pos) const{
    // Copies a substring [pos, pos+count) to character string pointed to by dest. If the requested substring lasts past the end of the string, or if count == npos, the copied substring is [pos, size()). The resulting character string is not null-terminated. 
    if(pos > this->size()) return 0; //should throw an std::out_of_rage
    if(pos + count > this->size()) count = this->size() - pos;
    unsigned int destIdx = 0;
    for(unsigned int i = pos; i < pos + count; ++i) dest[destIdx++] = this->buffer[i];
    return count;
} 

/*
Resizes the string to contain count characters.
If the current size is less than count, additional characters are appended.
If the current size is greater than count, the string is reduced to its first count elements.
The first version initializes new characters to CharT(), the second version initializes new characters to ch. 
*/
void BasicString::resize(unsigned int count){
    if(count < 1 || count > this->max_size() || count == npos) throw std::length_error("resize length error");

    
    if(count > this->size()){
        char *newBuffer ;
        try{
            newBuffer = new char[sizeof(char) * count+1];
            for(unsigned int i = 0; i < count+1; ++i) newBuffer[i] = '\0';
        } catch (const std::bad_alloc& ba){
            std::cerr << "BasicString resize(): memory allocation failure: " << ba.what()<<"\n";
        }
        for(unsigned int i = 0 ; i < this->size(); ++i) newBuffer[i] = this->buffer[i];
        delete[] this->buffer;
        this->buffer = newBuffer;
        if(this->bufferCap < count) this->bufferCap = count;

    } else if(count < this->size()){
        for(unsigned int i = count; i < this->size(); ++i) this->buffer[i] = '\0';
    }
    this->bufferSize = count;
}
void BasicString::resize(unsigned int count, char c){
    if(count < 1 || count > this->max_size() || count == npos) throw std::length_error("resize length error");


    if(count > this->size()){
        char *newBuffer ;
        try{
            newBuffer = new char[sizeof(char) * count+1];
            for(unsigned int i = 0; i < count+1; ++i) newBuffer[i] = '\0';
        } catch (const std::bad_alloc& ba){
            std::cerr << "BasicString resize(): memory allocation failure: " << ba.what()<<"\n";
        }
        
        for(unsigned int i = 0 ; i < this->size(); ++i) newBuffer[i] = this->buffer[i];
        for(unsigned int i = this->size(); i < count; ++i) newBuffer[i] = c;
        delete[] this->buffer;
        this->buffer = newBuffer;
        this->bufferCap = count;

    } else if(count < this->size()){
        for(unsigned int i = count; i < this->size(); ++i) this->buffer[i] = '\0';
    }
    this->bufferSize = count;
}

void BasicString::swap(BasicString &other) noexcept{
    using std::swap;
    unsigned int i = other.size();
    swap(this->bufferSize, i);
    swap(this->buffer, other.buffer);
}

unsigned int BasicString::find(const BasicString &str, unsigned int pos) const{
    //Finds the first substring equal to str.
    if(pos > str.size()) return npos; 
    for(unsigned i = pos; i < this->size(); ++i){
        
        if(this->buffer[i] == str.at(0)){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(start < str.size() && thisStart < pos + str.size()) if(this->at(thisStart++) != str.at(start++)) break;
            if(start >= str.size() && thisStart >= pos+ str.size() ) return i; 
        } 
    }
    return npos;

} 
unsigned int BasicString::find(const char *s, unsigned int pos , unsigned int count) const{
    // Finds the first substring equal to the range [s, s+count). This range may contain null characters. 
    for(unsigned i = pos; i < this->size(); ++i){

        if(this->buffer[i] == s[0]){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(s[start] != '\0' && thisStart < pos + count) if(this->at(thisStart++) != s[start++]) break;
            if(s[start] == '\0' && thisStart >= pos+ count ) return i; 
        }
    }
    return npos;
} 
unsigned int BasicString::find(const char *s, unsigned int pos ) const{
    // Finds the first substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    
    for(unsigned i = pos; i < this->size(); ++i){
        if(this->buffer[i] == s[0]){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(s[start] != '\0' && thisStart < this->size()) if(this->at(thisStart++) != s[start++]) break;
            if(s[start] == '\0' && i >= pos && i + start <= this->size()) return i; 
        }
    }
    //if()
    return npos;
} 
unsigned int BasicString::find(char c, unsigned int pos) const{
    // Finds the first character ch (treated as a single-character substring by the formal rules below).
    for(unsigned i = pos; i < this->size(); ++i) if(this->at(i) ==  c) return i;
    return npos;
} 


unsigned int BasicString::rfind(const BasicString &str, unsigned int pos ) const{
    // Finds the last substring equal to str.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    if(pos > str.size()) return npos; 
    for(unsigned i = pos; i != npos; --i){
        
        if(this->buffer[i] == str.at(0) &&  pos - i >= str.size()){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(start < str.size() && thisStart < pos) {
                if(this->at(thisStart) != str.at(start)) break;
                ++thisStart;
                ++start;
            }
            if(start >= str.size() && thisStart <= pos ) return i; 
        } 
    }
    return npos;
} 
unsigned int BasicString::rfind(const char *s, unsigned int pos , unsigned int count) const{
    // Finds the last substring equal to the range [s, s+count). This range can include null characters. 
     
    for(unsigned i = pos; i != npos; --i){
        
        if(this->buffer[i] == s[0] &&  pos - i >= count){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(s[start] != '\0' && thisStart < pos ) {
                if(this->at(thisStart) != s[start]) break;
                ++start;
                ++thisStart;
            }
            if(s[start] == '\0' && thisStart <= pos ) return i; 
        } 
    }
    return npos;
    
} 
unsigned int BasicString::rfind(const char *s, unsigned int pos ) const{
    // Finds the last substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    if(pos >= this->size() || pos == npos) pos = this->size()-1; 
    for(unsigned i = pos; i != npos; --i){
        
        if(this->buffer[i] == s[0] ){
            unsigned int start = 0;
            unsigned int thisStart = i;
            while(s[start] != '\0' && thisStart < pos ) {
                if(this->at(thisStart) != s[start]) break;
                ++start;
                ++thisStart;
            }
            if(s[start] == '\0' && thisStart <= pos ) return i; 
        } 
    }
    return npos;
} 
unsigned int BasicString::rfind(char c, unsigned int pos ) const{
    //  Finds the last character equal to ch.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        if(this->buffer[i] == c) return i; 
    }
    return npos;
} 


unsigned int BasicString::find_first_of(const BasicString &str, unsigned int pos) const{
    //Finds the first character equal to one of the characters in str.
    if(pos >= this->size()) throw std::length_error("pos is too large");
    for(unsigned i = pos; i < this->size(); ++i){
        for(unsigned i2 = 0; i2 < str.size(); ++i2 ) if(this->at(i) == str.at(i2)) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_of(const char *s, unsigned int pos , unsigned int count) const{
    // Finds the first character equal to one of the characters in the range [s, s+count). This range can include null characters.
    if(pos >= this->size()) throw std::length_error("pos is too large");
    for(unsigned i = pos; i < this->size(); ++i){
        for(unsigned i2 = 0; i2 < count; ++i2 ) if(this->at(i) == s[i2]) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_of(const char *s, unsigned int pos ) const{
    // Finds the first character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    if(pos >= this->size()) throw std::length_error("pos is too large");
    for(unsigned i = pos; i < this->size(); ++i){
        for(unsigned i2 = 0; s[i2] != '\0'; ++i2 ) if(this->at(i) == s[i2]) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_of(char c, unsigned int pos ) const{
    // Finds the first character equal to ch.
    if(pos >= this->size()) throw std::length_error("pos is too large");
    for(unsigned i = pos; i < this->size(); ++i){
        if(this->at(i) == c) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_not_of(const BasicString &str, unsigned int pos ) const{
    //Finds the first character equal to none of characters in str. 
    if(pos >= this->size()) pos = this->size()-1;
    for(unsigned i = pos; i < this->size(); ++i){
        unsigned idx2 = 0;
        while(idx2 < str.size()) {
            if(str.at(idx2)== this->at(i)) break;
            ++idx2;
        }
        if(idx2 >= str.size()) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_not_of(const char *s, unsigned int pos , unsigned int count) const{
    //  Finds the first character equal to none of characters in range [s, s+count). This range can include null characters.
    if(pos >= this->size()) pos = this->size()-1;
    for(unsigned i = pos; i < this->size(); ++i){
        unsigned idx2 = 0;
        while(idx2 < count) {
            if(s[idx2] == this->at(i)) break;
            ++idx2;
        }
        if(idx2 >= count) return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_not_of(const char *s, unsigned int pos ) const{
    // Finds the first character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    if(pos >= this->size()) pos = this->size()-1;
    for(unsigned i = pos; i < this->size(); ++i){
        unsigned idx2 = 0;
        while(s[idx2] != '\0') {
            if(s[idx2] == this->at(i)) break;
            ++idx2;
        }
        if(s[idx2] == '\0') return i;
    }
    return npos;
} 
unsigned int BasicString::find_first_not_of(char c, unsigned int pos ) const{
    // Finds the first character equal to ch.
    if(pos >= this->size()) pos = this->size()-1;
    for(unsigned i = pos; i< this->size(); ++i) if(this->at(i) != c) return i;
    return npos;
} 
unsigned int BasicString::find_last_of(const BasicString &str, unsigned int pos) const{
    //Finds the last character equal to one of the characters in str.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        for(unsigned i2 = 0; i2 < str.size(); ++i2 ) if(this->at(i) == str.at(i2)) return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_of(const char *s, unsigned int pos , unsigned int count) const{
    // Finds the last character equal to one of the characters in the range [s, s+count). This range can include null characters.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        for(unsigned i2 = 0; i2 < count; ++i2 ) if(this->at(i) == s[i2]) return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_of(const char *s, unsigned int pos ) const{
    // Finds the last character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        for(unsigned i2 = 0; s[i2] != '\0'; ++i2 ) if(this->at(i) == s[i2]) return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_of(char c, unsigned int pos ) const{
    // Finds the last character equal to ch.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        if(this->at(i) == c) return i;
    }
    return npos;
}


unsigned int BasicString::find_last_not_of(const BasicString &str, unsigned int pos ) const{
    //Finds the last character equal to none of characters in str. 
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        unsigned idx2 = 0;
        while(idx2 < str.size()) {
            if(str.at(idx2)== this->at(i)) break;
            ++idx2;
        }
        if(idx2 >= str.size()) return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_not_of(const char *s, unsigned int pos , unsigned int count) const{
    //  Finds the last character equal to none of characters in range [s, s+count). This range can include null characters.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        unsigned idx2 = 0;
        while(idx2 < count) {
            if(s[idx2] == this->at(i)) break;
            ++idx2;
        }
        if(idx2 >= count) return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_not_of(const char *s, unsigned int pos ) const{
    // Finds the last character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i){
        unsigned idx2 = 0;
        while(s[idx2] != '\0') {
            if(s[idx2] == this->at(i)) break;
            ++idx2;
        }
        if(s[idx2] == '\0') return i;
    }
    return npos;
} 
unsigned int BasicString::find_last_not_of(char c, unsigned int pos ) const{
    // Finds the last character equal to ch.
    if(pos >= this->size() || pos == npos) pos = this->size()-1;
    for(unsigned i = pos; i != npos; --i) if(this->at(i) != c) return i;
    return npos;
} 

// namespace myStrImp{
//     typename BasicString String;
// }