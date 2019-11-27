#include <vector>
using std::vector;
using std::swap;

/*

Problem originally from: https://leetcode.com/problems/move-zeroes/

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Note:
    * You must do this in-place without making a copy of the array.
    * Minimize the total number of operations.
    * 

    There are four main ways to do this problem.
*/


/*
First find count all the zeroes in the array. Second, create a new array storing all non-zero numbers as you go to ensure ordering. Third, put the number of zeroes that you counted
at the beggining to the end of the new array. Fourth, replcae all elements of the original array with the new array.
This solution works but it we can do better.

Runtime: O(n), where n is the number of total elements in the original array.
Space: O(n), Since we are creating a new array holding the same number of elements as the original array.  
*/
void moveZerores1(vector<int> &nums){
    if(nums.size() == 1 || nums.empty()) return ;

    int numZerores = 0;
    for(int i = 0; i< nums.size(); i++) if(nums.at(i) == 0) numZerores++;

    vector<int> correctOrder;
    for(int i = 0; i < nums.size(); i++) if(nums.at(i)!= 0) correctOrder.push_back(nums.at(i));
    for(int i =0; i < numZerores; i++ ) correctOrder.push_back(0);
    
    for(int i = 0; i < correctOrder.size(); i++) nums.at(i) = correctOrder.at(i);
}


/*
The second way to do this is to first count the number of zeroes in the array. Second, loop through the array to move all nonzero elements the the next availabe position (got to keep track of the next availabe slot).
Third, loop through the array starting from the end and append the number of zeroes. This solution is definitely better.

Runtime: O(n), where n is the number of total elements in the original array.
Space: O(1), no extra space is used.
*/
void moveZeroes2(vector<int>& nums){
    if(nums.size() == 1 || nums.empty()) return ;
        
    int numZeroes = 0; 
    int emptySlotIdx = 0;
    for(int i = 0 ; i < nums.size(); i++){
        if(nums.at(i) == 0) numZeroes++;
    }
        
    for(int i = 0; i < nums.size(); i++){
        if(nums.at(i) == 0 ) continue;
        nums.at(emptySlotIdx++) = nums.at(i);
    }
        
    for(int i = nums.size()-1; i > nums.size()-1-numZeroes; i--) nums.at(i) = 0;
}


/*
This solution builds on top of the last solution. Since we loop through the array keeping track of the next available slot for each non-zero number we can skip counting the number of zeroes
in the array since we know that once we finish looping through we would have finished placing all non-zero numbers in its correct place and the next available slot would be the start of the zeroes.
So you can fill all elements with zeroes form the next available slots to the end of the array.

Runtime: O(n), where n is the number of total elements in the original array.
Space: O(1), no extra space is used.
*/
void moveZeroes3(vector<int>& nums){
    if(nums.size() == 1 || nums.empty()) return ;
        
    int numZeroes = 0; 
    int emptySlotIdx = 0;
    for(int i = 0; i < nums.size(); i++){
        if(nums.at(i) == 0 ) continue;
        nums.at(emptySlotIdx++) = nums.at(i);
    }
        
    for(int i = emptySlotIdx; i <  nums.size(); i++) nums.at(i) = 0;
}


/*
This solution builds on top of the last solution. Since we loop through the array keeping track of the next available slot (starting from 0) for each non-zero number we can just 
loop through the array swapping the current index with the next available spot (updating the next available slot of course).

Runtime: O(n), where n is the number of total elements in the original array.
Space: O(1), no extra space is used.
*/
void moveZeroes4(vector<int>& nums){
    if(nums.size() == 1 || nums.empty()) return ;
        
    int currAvailableSlot = 0;
    int start = 0; 
    int end = nums.size()-1;
    while(start <= end){
        if(nums.at(start) != 0){
            swap(nums.at(currAvailableSlot++), nums.at(start));
        }
        start++;
    }
}