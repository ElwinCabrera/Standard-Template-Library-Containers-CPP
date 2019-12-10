#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using std::unordered_map;
using std::string;
using std::vector;
using std::sort;


/*
Given a string, write a function to check if it is a permutation of a palindrome. A palindrome is a word or phrase that is the same forwars and backwords.
A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

Example:
    Input: "Tact Coa"
    Output: true (permutations: "taco cat", "atoco cta", ect.)
*/


/*
One thing to note here is that it helps knowing what every palindrome consists of. There are two ways to identify a palindrome the first every character has an even number of repetitions.
The second way to identify a palindrome is if there is at most one character with no repetitions and every other character has an even number of repetitions. Here we created
an array to represent all the ascii codes and initalized it with all zeroes. After that we simply iterated through the string checking if it is a valid character of the alphabet and if the 
character is upper case we converted it to lower case at the same time we get the ascii code and at that position in the ascii code array we update the frequency for that character.
After that we iterate over the ascii code array and check if we have a palindrome using the definition of palindrome mentioned above.

Runtime: O(s) - where s is the length of the string
Space: O(1) - we dont use any extra space as we know exactly how much space will be used with the array
*/
bool isPalindromePermutation(const string &s){
    int asciiCodes[128];

    for(int i  = 0; i < 128; i++) asciiCodes[i] = 0;

    for(int i = 0 ; i < s.size(); i++) {
        char c = s.at(i);
       if(c >='A' && c <= 'Z') c += ' '; // or 32 in decimal to convert to lowercase
       if( c >= 'a' && c <= 'z') asciiCodes[s.at(i)-'a']++;
    }
    
    int singleCharCount = 0;
    for(int i = 0; i < 128; i++){
        if(asciiCodes[i] == 1) singleCharCount++;
        if(singleCharCount > 1) return false;
        if(asciiCodes[i] % 2 != 0 && asciiCodes[i] != 1) return false;
    }

    return true;
}


/*
This way is similar to the one above except we use a map instead of a array to count the frequency of each character.

Runtime: O(s) - where s is the length of the string
Space: O(n) - where n is the length of every unique character 
*/
bool isPalindromePermutation2(const string &s){
   unordered_map<char, int> map; 
   
   for(int i = 0; i < s.size(); i++){
       char c = s.at(i);
       if(c >='A' && c <= 'Z') c += ' '; // or 32 in decimal to convert to lowercase
       if( c >= 'a' && c <= 'z') {
           auto it  = map.find(c);
           if(it != map.end()) it->second++;
           else map.insert({c, 1});
       }
   }

    int foundOddCount = 0;

    for(auto it = map.begin(); it != map.end(); it++){
        if(it->second == 1) foundOddCount++;
        if(it->second %2 != 0 && it->second != 1) return false;
        if(foundOddCount > 1) return false; 
    }

    return true;
}


/*
Here we take a different approach. Instead of storing the frequency of letters in some sort of storage we can sort the array and count the frequncy for each character as we iterate over our 
string. if at any point we find that the frequency is odd or that there are more than one unique characters we can return false. 

Runtime: O(slogs) - where s is the size of the string
Space: O()
*/
bool isPalindromePermutation3(string &s){
    for(int i = 0; i < s.size(); i++) if(s.at(i) >= 'A' && s.at(i) <= 'Z') s.at(i) += ' ';  // or 32 in decimal to convert to lowercase
    sort(s.begin(), s.end());
    
    int lastFreq = 0;
    int foundOddCount = 0;
    for(int i = 1 ; i < s.size(); i++){
        if(s.at(i) >='a' && s.at(i) < 'z'){
            if(s.at(i) == s.at(i -1)) lastFreq++;
            else{
                if(lastFreq == 1 ) foundOddCount++; 
                if(lastFreq %2 != 0 && lastFreq != 1) return false;
                if(foundOddCount > 1) return false;
            }
        }
    }
    return true;
    

}