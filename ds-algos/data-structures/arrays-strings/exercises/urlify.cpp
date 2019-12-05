#include <iostream>
#include <string>
using std::string;
using std::cout;

/*
Source: Cracking the Coding interview pg. 90

Write a method to replace all spaces in a string with '%20'. You may assume that the string has sufficeint space at the end to hold the additional 
characters, and that you are given the 'true' length of the string.

Example:
Input:  "Mr John Smith    ", 13
Output: "Mr%20John%20Smith"
*/


/*
 Since we know when the string actually ends we dont need to iterate to get the last position/character of the string. Using that knowledge we can start by shifting the 
 string all the way to the right. You can do this by having a pointer to the last position of the array and another pointer to the last position of the string and then swaping those 
 updating each pointer to move to the left by one each time. Now that the string is shifted all the way to the right we can begin urlifing it. We will need two things, the first is 
 a pointer to the beginning character of the shifted string and second another pointer to the beggining of the whole array. We move both pointers to the left by one as long as the pointer pointing
 to the start of the array is less than the whole string array. However, whenever the pointer pointing to the string encounters a space we add three characters '%20' at the index that the other pointer 
 is pointing at (the one pointing at the whole array) and update the coresponding pointer accordingly(move it by 3 chars). At the end we should have a urlified string that uses up all the space.  

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