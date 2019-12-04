#include <string>
using std::string;

/* 
    Source: Cracking the Coding interview pg. 90

    Given two strings write a method to determine if one is a permutation of the other
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