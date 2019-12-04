#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
using std::cout;
/* 
 
 Source: Cracking the Coding interview pg. 90

 Implement an algorithm to determine if a string has all unique characters. What if you can not use any additional data structures. 
*/

bool isUnique(const string &s){

    bool charPos[128];
    for(int i = 0 ; i < s.size(); i++){
        if(charPos[s.at(i) - 'a']) return false;
        charPos[s.at(i) - 'a'] = true;
    }
    return true;
    
}