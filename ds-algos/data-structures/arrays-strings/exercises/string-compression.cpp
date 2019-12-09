#include <string>
#include <sstream>
#include<vector>
using std::string;
using std::stringstream;
using std::to_string;

/*
Source: Source: Cracking the Coding interview pg. 91

Implement a method to perform basic string compression using the counts of repeated characters. For example, the string "aabbcccccaaa" would become "a2b1c5a3". If the compressed 
string would not become smaller than the original string, your method should retrun the original string. You can assume the string has only uppercase and lowercase letters (A-Za-z).
*/

/*This is relatively a straight forward problem. For every character in the string you check the last character to see if it is the same as the current character you are iterating at. If that character is the 
same we can add one to a counter that counts the frequency of characters the same, however if the last character is not the same as the current character we can add the last character to and the 
counter we had to measeure frequency of characters to a resulting string. We do those two steps mentioned for each character in string. 

Note: 
"C++ strings are mutable, and pretty much as dynamically sizable as a StringBuffer. Unlike its equivalent in Java, this code wouldn't create a new string each time; it just appends to the current one." - https://stackoverflow.com/questions/15400508/string-concatenation-complexity-in-c-and-java

In Java strings are immutable. Below is an explanation of how string concatenation works in Java, and why it cost O(n^2) 

"Now, what is true is that if you build a string one character at a time (for instance String hello = 'h' + 'e' + 'l' + 'l' + 'o', that will be O(n^2). I'm guessing that's what you're responding to, so I'll try to explain that.
Since java strings are immutable each + gets you a new copy of the string. So as you were saying, first you build "h", then "he", then "hel" and so on. Let's suppose I have an n character string. The first + requires building a string of length 2. 
The next plus requires building a string of length 3, and so on for a total cost of 2 + 3 + ... + n. This is the arithmetic series (minus 1, but constant differences don't affect big-O). The sum of the arithmetic series is (n^2 + n) / 2, which is O(n^2) (dividing by 2 doesn't change that!). 
So, assuming that's what you were wondering about, I hope that helps!" - https://www.reddit.com/r/learnjava/comments/7cjpfh/why_is_string_concatenation_on2/

In Java you can overcome this by using a class called StringBuilder this is mutable and will give you linear time. In C++ there is a similar class called stringstream and gives you more flexibility but will not run any faster than just std::string as both run linear time.

Runtime: O(n)
Space: O(1)
*/
string compressString(const string &s){
    if(s.size() == 1 || s.size() == 0) return s;
    
    string compressedStr = "";
    int charFreq = 1;

    for(int i = 1; i < s.size(); ++i){
        if(s.at(i) != s.at(i-1)){
            compressedStr += s.at(i-1) + to_string(charFreq);
            charFreq = 1;
        } else ++charFreq;
    }
    compressedStr += s.at(s.size()-1) + to_string(charFreq);
    
    return (compressedStr.size() <= s.size()) ? compressedStr:s; 
}