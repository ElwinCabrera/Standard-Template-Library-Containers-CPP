#include <iostream>
#include <string>
using std::string;
using std::cout;

/*
Source: Cracking the Coding interview pg. 90

Write a method to replace all spaces in a string with '%20'. You may assume that the string has sufficeint space at the end to hold the additional 
characters, and that you are given the 'true' length of the string.
*/
void urlify(string &s, int trueStringSize){
    
    int end = s.size() - 1;
    for(int i = trueStringSize-1; i >=0; i--) {
        s.at(end) = s.at(i);
        s.at(i) = ' ';
        end--;
    }
    
    int currStrIdx = s.size()- trueStringSize ;
    int start = 0;

    while( start < s.size()) {
        if(s.at(currStrIdx) == ' '){
            s.at(start) = '%';
            s.at(start+1) = '2';
            s.at(start+2) = '0';
            start = start +3;
            
        } else s.at(start++) = s.at(currStrIdx);
        currStrIdx++;        
    }
}