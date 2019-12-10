#include<string>
#include <algorithm>    // std::find
using std::string;
using std::find;

/*

Source: Source: Cracking the Coding interview pg. 91


Assume you have a method isSubstring which if one word is a substring of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only 
one call to isSubstring (eg. "waterbottle" is a rotation of "erbottlewat")
*/


/*
One way to do this is to find the rotation point by comparing all characters of the rotation string with the first character of the non rotated string if at any point you find a match then you can iterate over 
the non rotated string starting at the beginning comparing it with the rotated string starting at the found rotation point comparing each character at each rotation for both strings, if you reach then end of the string 
of the rotated array then just update the index to 0 and continue the iteration until we reach the end of the non rotated string.

Runtime O(s) - where s is the length of the string
Space: O(1) 
*/
bool isSubstring(const string &s1, const string &s2){
    if(s1.size() != s2.size()) return false;
    
    for(int i1 = 0; i1 < s1.size(); ++i1){
        if(s1.at(i1) == s2.at(0)){
            int i2 = 0;
            int startIdx = i1;
            for(; i2 < s2.size(); ++i2){
                if(startIdx >= s1.size()) startIdx = 0;
                if(s2.at(i2) != s1.at(startIdx++)) break; 
            }
            if(i2 == s1.size()) return true;
        }
    }
    return false;
}

/*
Another approach is concatenate the non rotated string 's1' with itself and store that in a new variable therefore s2 will be a substring in the new string (s1+s1) this
we can just use the find function on the new string to find the rotated strind s2

Runtime: O(s) - where s is the length of the string
Space: O(1)
*/
bool isSubstring2(const string &s1, const string &s2){
    if(s1.size() != s2.size()) return false;
    string s1s1 = s1 +s1;
    auto it = s1s1.find(s2);
    return ( it != string::npos);
}