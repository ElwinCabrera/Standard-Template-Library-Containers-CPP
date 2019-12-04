#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
using std::cout;
/* 
 
 Source: Cracking the Coding interview pg. 90

 Implement an algorithm to determine if a string has all unique characters. What if you can not use any additional data structures. 
*/

/*
Here you can have a boolean array of the length of the whole ascii character set. Iterate over the string and at each iteration find the corresponding ascii code for
that character in the string and check if the boolean array at the ascii code number is true then you can immediately return false. However, if the boolean array at the ascii code number is true
is false then just set that position to true and continue on. This function will return true only when the ascii code number for a given character has only been access/visited once.
*/
bool isUnique(const string &s){

    bool charPos[128];
    for(int i = 0 ; i < s.size(); i++){
        if(charPos[s.at(i) - 'a']) return false;
        charPos[s.at(i) - 'a'] = true;
    }
    return true;
    
}

/*
If you know for sure that all characters in the string will be lowercase a-z then you could use a bit vector (simply just a regular int placing each bit accordingly) and a little bit manipulation.
since we know that the english alphabet is only 26 characters long we can just use a simple integer to represent all of our bits (since integers hold 4 bytes or 32 bits). 
We can then iterate over our string converting each character to its coresponding ascii number and then just shifting 1 to the left by that ascii number to corespond the position in our bit vector.
Whenever we do an interation we have to check if that positon in our pit vector is already on (you can do this by an AND/& operator) a one, if it is then we can return false immediately if not we can
continue our iteration.  
*/
bool isUnique2(const string &s){

    int bits = 0;
    for(int i = 0 ; i < s.size(); i++){
        int asciiVal = s.at(i) - 'a';
        if(bits & (1 << asciiVal)) return false;
        bits += 1 << asciiVal;
    }
    return true;
    
}

