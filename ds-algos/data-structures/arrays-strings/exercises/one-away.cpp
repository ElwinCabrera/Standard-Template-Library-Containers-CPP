#include <string>
using std::string;


/*
Source: Source: Cracking the Coding interview pg. 91

There are three types of edits that can be performed on strings: insert a character, remove a character, or replace a character. Given two strings, write a function 
to check if they are one edit (or zero edits) away.

Example:

"pale",  "ple"  -> true
"pales", "pale" -> true
"pale",  "bale" -> true
"pale",  "bake" -> false
*/




/*
The trick to this problem is to notice that there are two unique situation for any other situation we can retrun false. The first being that one of the string is longer than the other by just one. 
The second situation is where both strings are the same length but not the same. For the first situation we can simply check both strings character by character at the same time and when we reach a character 
that does not math on we move the pointer for the longer string by one, doing this allows the smaller string to catch up and if you notice more than one character that do not match 
we can immediately return false as it can not be more than one away. For the second situation where the string are the same length we can simply iterate over one string comparing it with the 
other string and keeping score of the number of different character, if the number of different character is more than one we can immediately return false.

Runtime: O(s) - where s is the length of the shorter string, we never iterate past that.
Space: O(1) - no extra memory is used

*/
bool oneEditInsert(const string &s1, const string &s2);

bool isOneAway(const string &s1, const string &s2){
    if(s1 == s2) return true;
    if(s1.size() == s2.size()){
        int diffCount = 0;
        for(int i = 0; i< s1.size(); ++i){
            if(s1.at(i) != s2.at(i)) ++diffCount;
            if(diffCount > 1) return false;
        }
    } else if(s1.size() + 1 == s2.size()) return oneEditInsert(s1, s2);
      else if(s1.size() - 1 == s2.size()) return oneEditInsert(s2, s1);
      else return false;
    
    return true;  
}

bool oneEditInsert(const string &s1, const string &s2){
    int start1 = 0; 
    int start2 = 0;
    while(start1 < s1.size() && start2 < s2.size()){
        if(s1.at(start1) != s2.at(start2)){
            if(start1 != start2) return false;
            ++start2;
        } else {
            ++start1;
            ++start2;
        }
    }
    return true;
}