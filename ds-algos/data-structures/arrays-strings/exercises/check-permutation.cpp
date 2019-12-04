#include <string>
using std::string;

/* 
    Source: Cracking the Coding interview pg. 90

    Given two strings write a method to determine if one is a permutation of the other
*/


/*

One way to do this is to have a integer array the size of the total number of ascii codes and iterate over the one string and for every character find the ascii code for that character and
use that as index for the integer array then increment by one  at that index. Then  iterate over the other string and do the same thing except you are going to decrement by one and if at any point 
the number at that index is less than zero immediately return false as this string has too many of the current character. This function will only return true when all values in the integer 
array are zero.
*/
bool isPermutation(const string &s1, const string &s2){
    int charSet[128];
    for(int i = 0 ; i < 128; i++) charSet[i] = 0;
    
    for(int i = 0; i < s1.size(); i++) charSet[s1.at(i)-'a']++;
    
    for(int i = 0 ; i < s2.size(); i++){
        charSet[s2.at(i)-'a']--;
        if(charSet[s2.at(i)-'a'] < 0 ) return false;
    }

    return true;
    
}