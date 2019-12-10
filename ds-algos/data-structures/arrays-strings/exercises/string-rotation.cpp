#include<string>
using std::string;


/*

Source: Source: Cracking the Coding interview pg. 91


Assume you have a method isSubstring which if one word is a substring of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only 
one call to isSubstring (eg. "waterbottle" is a rotation of "erbottlewat")
*/

bool isSubstring(const string &s1, const string &s2){
    
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