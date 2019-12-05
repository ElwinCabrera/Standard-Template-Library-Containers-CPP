/*
Original: https://leetcode.com/problems/valid-parentheses/

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true

Example 2:

Input: "()[]{}"
Output: true

Example 3:

Input: "(]"
Output: false

Example 4:

Input: "([)]"
Output: false

Example 5:

Input: "{[]}"
Output: true
*/

#include <string>
#include <stack>
using std::stack;
using std::string;

/*
One way to do this is to use a stack. We could iterate over the string and at any point we see any opening parentheses we push that to the stack and when we see any closing 
parentheses we can pop the last pushed item and check if it has a matching opening parentheses. If the popped item does have a mathing set then continue iterating over the string
however if the popped item does not match then immediately return false as it is not a valid. 

*/
bool isValid(const string &s){
    stack<char> st;
    for(int i = 0 ; i < s.size(); i++){
        if(s.at(i) == '(' || s.at(i) == '[' || s.at(i) == '{'){
            st.push(s.at(i));
        } else { 
            char top = st.top();
            if(s.at(i) == ')' ) if(top != '(') return false;
            if(s.at(i) == ']') if(top != '[') return false;
            if(s.at(i) == '}') if(top != '{') return false;
            
            st.pop();
        }

    }

    return st.empty();
}