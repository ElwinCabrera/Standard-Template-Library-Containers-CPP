/*

Original: https://leetcode.com/problems/longest-common-prefix/

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"

Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Note:

All given inputs are in lowercase letters a-z.



*/


#include<vector>
#include<string>
using std::string;
using std::vector;

string longestCommonPrefix(vector<string>& strs) {
    if(strs.empty()) return "";
    string result = strs.at(0);
        
    for(int i = 1; i< strs.size(); i++){
        string newLCP = getLCP(result, strs.at(i));
        result = newLCP;
    }
        
    return result;
}
    
string getLCP(string s1, string s2){
    int shortestStr = (s1.size() < s2.size()) ? s1.size():s2.size();
    string lcp = "";
    for(int i = 0; i < shortestStr; i++){
        if(s1.at(i) == s2.at(i)) lcp.push_back(s1.at(i));
        else break;
    }
    return lcp;
}