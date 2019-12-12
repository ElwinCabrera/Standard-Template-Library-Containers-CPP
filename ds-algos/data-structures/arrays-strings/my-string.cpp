#include <stdexcept>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <climits>
#include <math.h>

class BasicString{
public:

    typedef BasicString String;
    typedef char* iterator;
    static const unsigned int npos = -1;

    /*************** Member functions **************/
    BasicString(): buffer(nullptr), bufferSize(0), bufferCap(0) {}
    BasicString(const char c, unsigned int count);
    BasicString(const BasicString &other); //Copy Constructor
    BasicString(BasicString &&other) noexcept; //Move constructor
    ~BasicString();
    BasicString& operator=(const BasicString &str);
    BasicString& operator=(BasicString &&other);
    void assign(unsigned int count, const char c);



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
    void shrinkToFit();



    /*************** Operations **************/
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
    BasicString& replace(unsigned int pos, unsigned int count, const BasicString &str); //string str
    BasicString& replace(const iterator first, const iterator last, const BasicString &str); //string str 
    BasicString& replace(unsigned int pos, unsigned int count, const BasicString &str, unsigned int pos2, unsigned int count2);  // substring [pos2, pos2 + count2) of str, except if count2==npos or if would extend past str.size(), [pos2, str.size()) is used.
    BasicString& replace(unsigned int pos, unsigned int count, const char *cstr, unsigned int count2); // characters in the range [cstr, cstr + count2);
    BasicString& replace(const iterator first, const iterator last, const char *cstr, unsigned int count2); // characters in the range [cstr, cstr + count2);
    BasicString& replace(unsigned int pos, unsigned int count, const char *cstr); // characters in the range [cstr, cstr + Traits::length(cstr));
    BasicString& replace(const iterator first, const iterator last, const char *cstr); // characters in the range [cstr, cstr + Traits::length(cstr));
    BasicString& replace(unsigned int pos, unsigned int count, unsigned int count2, char c); // count2 copies of character ch;
    BasicString& replace(const iterator first, const iterator last, unsigned int count2, char c); // count2 copies of character ch;
    BasicString substr(unsigned int pos , unsigned int count) const; // Returns a substring [pos, pos+count). If the requested substring extends past the end of the string, or if count == npos, the returned substring is [pos, size()). 
    unsigned int copy(char *dest, unsigned int count, unsigned int pos) const; // Copies a substring [pos, pos+count) to character string pointed to by dest. If the requested substring lasts past the end of the string, or if count == npos, the copied substring is [pos, size()). The resulting character string is not null-terminated. 
    /*
    Resizes the string to contain count characters.
    If the current size is less than count, additional characters are appended.
    If the current size is greater than count, the string is reduced to its first count elements.
    The first version initializes new characters to CharT(), the second version initializes new characters to ch. 
    */
    void resize(unsigned int count);
    void resize(unsigned int count, char c);
    void swap(BasicString &other);
    void swap(BasicString &other) noexcept;




    /*************** Search **************/
    unsigned int find(const BasicString &str, unsigned int pos = 0) const; //Finds the first substring equal to str.
    unsigned int find(const char *s, unsigned int pos , unsigned int count) const; // Finds the first substring equal to the range [s, s+count). This range may contain null characters.
    unsigned int find(const char *s, unsigned int pos = 0) const; // Finds the first substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int find(char c, unsigned int pos = 0) const; // Finds the first character ch (treated as a single-character substring by the formal rules below).
    unsigned int rfind(const BasicString &str, unsigned int pos ) const; // Finds the last substring equal to str.
    unsigned int rfind(const char *s, unsigned int pos , unsigned int count) const; // Finds the last substring equal to the range [s, s+count). This range can include null characters. 
    unsigned int rfind(const char *s, unsigned int pos ) const; // Finds the last substring equal to the character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int rfind(char c, unsigned int pos ) const; //  Finds the last character equal to ch.
    unsigned int findFirstOf(const BasicString &str, unsigned int pos = 0) const; //Finds the first character equal to one of the characters in str.
    unsigned int findFirstOf(const char *s, unsigned int pos , unsigned int count) const; // Finds the first character equal to one of the characters in the range [s, s+count). This range can include null characters.
    unsigned int findFirstOf(const char *s, unsigned int pos = 0) const; // Finds the first character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int findFirstOf(char c, unsigned int pos = 0) const; // Finds the first character equal to ch.
    unsigned int findFirstNotOf(const BasicString &str, unsigned int pos = 0) const; //Finds the first character equal to none of characters in str. 
    unsigned int findFirstNotOf(const char *s, unsigned int pos , unsigned int count) const; //  Finds the first character equal to none of characters in range [s, s+count). This range can include null characters.
    unsigned int findFirstNotOf(const char *s, unsigned int pos = 0) const; // Finds the first character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    unsigned int findFirstNotOf(char c, unsigned int pos = 0) const; // Finds the first character equal to ch.
    unsigned int findLastOf(const BasicString &str, unsigned int pos) const; //Finds the last character equal to one of the characters in str.
    unsigned int findLastOf(const char *s, unsigned int pos , unsigned int count) const; // Finds the last character equal to one of the characters in the range [s, s+count). This range can include null characters.
    unsigned int findLastOf(const char *s, unsigned int pos ) const; // Finds the last character equal to one of the characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int findLastOf(char c, unsigned int pos ) const; // Finds the last character equal to ch.
    unsigned int findLastNotOf(const BasicString &str, unsigned int pos ) const; //Finds the last character equal to none of characters in str. 
    unsigned int findLastNotOf(const char *s, unsigned int pos , unsigned int count) const; //  Finds the last character equal to none of characters in range [s, s+count). This range can include null characters.
    unsigned int findLastNotOf(const char *s, unsigned int pos ) const; // Finds the last character equal to none of characters in character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s).
    unsigned int findLastNotOf(char c, unsigned int pos ) const; // Finds the last character equal to ch.

    //operator+ ? 




private:
    char *buffer;
    unsigned int bufferSize;
    unsigned int bufferCap;
};



/*************** Member functions **************/
BasicString::BasicString(const char c, unsigned int count){
    this->bufferSize = count;
    this->buffer = nullptr;
    this->reserve(count+1);
    for(unsigned int i = 0; i < count; ++i) this->buffer[i] = c;
    this->buffer[count] = '\0';
}

BasicString::BasicString(const BasicString &other) {
    //Copy Constructor
    this->buffer = nullptr; 
    this->bufferSize = other.size();
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
    char *newBuffer;
    try{
        newBuffer = new char[(sizeof(char)* cap)];
    } catch (const std::bad_alloc& ba){
        std::cerr << "BasicString reserve(): memory allocation failure: " << ba.what()<<"\n";
    }

    if(buffer != nullptr){
        for(unsigned int i = 0 ; i < this->bufferSize; ++i) newBuffer[i] = this->buffer[i];
        for(unsigned int i = this->bufferSize; i < cap; ++i) newBuffer[i]= '\0';
        delete[] this->buffer;
        this->buffer = nullptr;
    }
    this->buffer = newBuffer;
    this->bufferCap = cap;
}

void BasicString::shrinkToFit() {
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
BasicString& BasicString::insert(unsigned int idx, unsigned int count, const char c) {
    // Inserts count copies of character ch at the position index
    if(idx + count >= this->bufferCap ) resize(idx + count);
    if(idx + count >= this->bufferSize) this->bufferSize = idx + count;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = c;
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const char* s) {
    // Inserts null-terminated character string pointed to by s at the position index. The length of the string is determined by the first null character using Traits::length(s). 
    unsigned int count = 0;
    const char *cptr = s;
    while(cptr != '\0') {
        cptr++;
        count++;
    }
    if(idx + count >= this->bufferCap ) resize(idx + count);
    if(idx + count >= this->bufferSize) this->bufferSize = idx + count;
    unsigned int idx2 = 0; 
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = s[idx2++]; 
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const char* s, unsigned int count) {
    //Inserts the characters in the range [s, s+count) at the position index. The range can contain null characters.
    if(idx + count >= this->bufferCap ) resize(idx + count);
    if(idx + count >= this->bufferSize) this->bufferSize = idx + count;
    unsigned int idx2 = 0;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = s[idx2++];
    return *this;
}
BasicString& BasicString::insert(unsigned int idx , const BasicString &str) {
    //Inserts string str at the position index
    if(idx + str.size() >= this->bufferCap ) resize(idx + str.size());
    if(idx + str.size() >= this->bufferSize) this->bufferSize = idx + str.size();
    unsigned int idx2 = 0;
    for(unsigned int i = idx; i < idx + str.size(); ++i) this->buffer[i] = str.at(idx2++);
    return *this;
}
BasicString& BasicString::insert(unsigned int idx, const BasicString &str, unsigned int index_str, unsigned int count) {
    // Inserts a string, obtained by str.substr(index_str, count) at the position index
    if(idx + count >= this->bufferCap ) resize(idx + count);
    if(idx + count >= this->bufferSize) this->bufferSize = idx + count;
    for(unsigned int i = idx; i < idx + count; ++i) this->buffer[i] = str.at(index_str++);
    return *this;
}
BasicString::iterator BasicString::insert(iterator pos, char c){
    // Inserts character c before the character pointed by pos
    *(pos -1) = c;
    return (pos-1);
}
void BasicString::insert(iterator pos, unsigned int count, char c) {
    // Inserts count copies of character ch before the element (if any) pointed by pos
    if(pos + count >= this->end()) resize(count);
    if(count >= this->bufferSize) this->bufferSize = count;
    pos -= 1;
    for(unsigned int i = 0; i < count; ++i) {
        *(pos) = c;
        pos++;
    } 
}

BasicString& BasicString::erase(unsigned int idx , unsigned int count ){
    //Removes min(count, size() - index) characters starting at index.
    count = std::min(count, this->size() - idx);
    for(unsigned int i = idx; i< idx+count; ++i) this->buffer[i] = '\0';
    unsigned int i1 = idx;
    unsigned int i2 = idx + count;
    
    while(i2 < this->bufferSize) this->buffer[i1++] = buffer[i2++];
    for(unsigned int i = idx + count; i < this->bufferSize; ++i) this->buffer[i] = '\0';
    this->bufferSize -= count; 

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
    
    unsigned int count = 0; 
    for(auto it = first; it != last; ++it) {
        *(it) = '\0';
        ++count;
    }
    auto left = first;
    auto right = last+1;
    while(last != this->end()) {
        *left = *right;
        left++;
        right++;
    }
    this->bufferSize -= count;
    return first;
    
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
} 
BasicString& BasicString::append(const BasicString &str){
    // Appends string str
    for(unsigned int i = 0; i < str.size(); ++i) this->push_back(str.at(i));
} 
BasicString& BasicString::append(const BasicString &str, unsigned int pos, unsigned int count){
    // Appends a substring [pos, pos+count) of str. If the requested substring lasts past the end of the string, or if count == npos, the appended substring is [pos, size()). If pos > str.size(), std::out_of_range is thrown. 
    if(pos == BasicString::npos) count = str.size();
    for(unsigned int i = pos; i < pos + count; ++i) this->push_back(str.at(i));
} 
BasicString& BasicString::append(const char* s, unsigned int count){
    // Appends characters in the range [s, s + count). This range can contain null characters.
    for(unsigned int i = 0; i < count; ++i) this->push_back(s[i]);
} 
BasicString& BasicString::append(const char* s){
    // Appends the null-terminated character string pointed to by s. The length of the string is determined by the first null character using Traits::length(s)
    for(unsigned int i = 0; s[i] != '\0'; ++i) this->push_back(s[i]);
} 
BasicString& BasicString::operator+= (const BasicString &str){
    //Appends string str
    for(unsigned int i = 0; i < str.size(); ++i) this->push_back(str.at(i));
} 
BasicString& BasicString::operator+= (char c){
    //Appends character ch
    this->push_back(c);
} 
BasicString& BasicString::operator+= (const char *s){
    // Appends the null-terminated character string pointed to by s.
    for(unsigned int i = 0; s[i] != '\0'; ++i) this->push_back(s[i]);
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
    if(count1 > this->size() - pos1) count1 = this->size();
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
    if(count1 > this->size() - pos1) count1 = this->size();
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
    if(count1 > this->size() - pos1) count1 = this->size();
    unsigned int size = std::min(count1, count2);
    for(unsigned int i = 0; i < size; ++i) {
        int diff = this->buffer[pos1++] - s[i];
        if(diff < 0 || diff >0) return diff;  
    }

    if(count1 < count2) return -1;
    else if(count1 > count2) return 1;
    
    return 0;
} 
bool BasicString::startsWith(BasicString &str) const{
    // a string str. (new in c++20)
    if(this->bufferSize < str.size()) return false;
    for(unsigned int i = 0 ; i < str.size(); ++i) if(this->buffer[i] != str.at(i)) return false;
    return true;
} 
bool BasicString::startsWith(char c) const noexcept{
    //a single character c. (new in c++20)
    return c == this->buffer[0];
} 
bool BasicString::startsWith(const char *s) const{
    //a null-terminated character string s. (new in c++20)
    for(unsigned int i = 0 ; s[i] != '\0'; ++i) {
        if(i > this->bufferSize || this->buffer[i] != s[i]) return false;
    }
    return true;
} 
bool BasicString::endsWith(BasicString &str) const{
    // a string str. (new in c++20)
    if(this->bufferSize > str.size()) return false;
    unsigned int idx1 = this->bufferSize -1;
    for(unsigned int i = str.size()-1; i >= 0; --i) if(str.at(i) != this->buffer[idx1--]) return false;
    return true;
} 
bool BasicString::endsWith(char c) const noexcept{
    //a single character c. (new in c++20)
    return this->buffer[this->bufferSize-1] == c;
} 
bool BasicString::endsWith(const char *s) const{
    //a null-terminated character string s. (new in c++20)
    unsigned int count =0;
    for(unsigned int i =0; i < s[i] != '\0'; ++i ) count++;
    if(this->bufferSize < count) return false;
    unsigned int idx1 = this->bufferSize-1;
    for(unsigned int i = count-1; i >=0; --i) if(this->buffer[idx1--] != s[i]) return false;
    return true;
}

BasicString& BasicString::replace(unsigned int pos, unsigned int count, const BasicString &str){
    //string str 
    //count is how many we chars we are replacing, if count is 0 then we are not replacing but inserting at that pos so we can just call insert(pos, str) in that case
    //if pos+ count is more than the this string length then we just append str starting from pos in this string 
    
    if(pos > this->size()) return *this; // not possible should return error
    if(count == 0) return this->insert(pos, str);
    
    int charsToEndCount = this->size() - pos;
    unsigned int idx = 0;
    unsigned int end = pos + count;
    
    if(end > this->size()) {
        this->resize(str.size()+(this->size()-charsToEndCount));
        while(idx < str.size()) this->buffer[pos++] = str.at(idx++);
    } else {
        while(pos < end) this->buffer[pos++] = str.at(idx++);
    } 

    return *this;
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const BasicString &str){
    //string str [first, last)
    
    if(first > this->begin()) return *this; // not possible should return error
    //if(first == last) return this->insert(first, last,str);
    
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
    // substring [pos2, pos2 + count2) of str, except if count2==npos or if would extend past str.size(), [pos2, str.size()) is used.
}  
BasicString& BasicString::replace(unsigned int pos, unsigned int count, const char *cstr, unsigned int count2){
    // characters in the range [cstr, cstr + count2);
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const char *cstr, unsigned int count2){
    // characters in the range [cstr, cstr + count2);
} 
BasicString& BasicString::replace(unsigned int pos, unsigned int count, const char *cstr){
    // characters in the range [cstr, cstr + Traits::length(cstr));
} 
BasicString& BasicString::replace(const iterator first, const iterator last, const char *cstr){
    // characters in the range [cstr, cstr + Traits::length(cstr));
} 
BasicString& BasicString::replace(unsigned int pos, unsigned int count, unsigned int count2, char c){
    // count2 copies of character ch;
} 
BasicString& BasicString::replace(const iterator first, const iterator last, unsigned int count2, char c){
    // count2 copies of character ch;
} 
BasicString BasicString::substr(unsigned int pos , unsigned int count) const{
    // Returns a substring [pos, pos+count). If the requested substring extends past the end of the string, or if count == npos, the returned substring is [pos, size()).
} 

unsigned int BasicString::copy(char *dest, unsigned int count, unsigned int pos) const{
    // Copies a substring [pos, pos+count) to character string pointed to by dest. If the requested substring lasts past the end of the string, or if count == npos, the copied substring is [pos, size()). The resulting character string is not null-terminated. 
} 

// namespace myStrImp{
//     typename BasicString String;
// }