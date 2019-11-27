/*
Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Note:

    * Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
    * Could you do it in-place with O(1) extra space?

*/

#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;


/*
One basic way to do this is just brute force. You can do this by rotating the entire array by one 'k' times.

Run time: O(k * n)
Space: O(1)
*/

void rotate1(vector<int>& nums, int k){

    for(int r = 0 ; r < k; r++){
        int lastElem = nums.at(nums.size()-1);
        for(int i = nums.size()-1; i >= 0; i--){
            if(i -1 >= 0) nums.at(i) = nums.at(i-1); 
        }
        nums.at(0) = lastElem;
    }


}






/*
Another way to do this is to find the pivot point (usually its at index 'k' but keep in mind that 'k' can be >= nums.size() so you would have to mod the nums.size and 'k').
Put all of the values in a map with their index as keys. Then loop through the array form the pivot index all the way to the end and getting the next index (in order )from the map.
Then do the same thing except from the beginning of the array up until but not including the pivot index.   

Run time: O(n)
Space: O(n)
*/
void rotate2(vector<int>& nums, int k) {
    if(k == 0 || nums.empty() || nums.size() == 1) return;
    unordered_map<int, int> idxToValueMap;
    
    for(int i = 0 ; i < nums.size(); i++){
        if(idxToValueMap.find(i) == idxToValueMap.end()) idxToValueMap.insert({i, nums.at(i)});
    } 

    int pivotIdx = k % nums.size();

    int getIdx = 0;
    for(int i = pivotIdx; i< nums.size(); i++) nums.at(i) = idxToValueMap.find(getIdx++)->second;
    for(int i = 0 ; i< pivotIdx; i++) nums.at(i) = idxToValueMap.find(getIdx++)->second;
}






/*
Another possible solution is to use an extra array of the same size as the original. First thing you would do is to loop through the new array putting in all the numbers in the correct 
position. Then copy over the array with the values in the correct position in the original array overriding the old values in each position. The way you get the correct position 
is by just using the rotation amount plus the current index to find its offest (of course you would want to mod that with the total size to not cause out of bounds).  

Run time: O(n)
Space: O(n)
*/
void rotate3(vector<int>& nums, int k) {
    if(k == 0 || nums.empty() || nums.size() == 1) return;
    
    vector<int> correct(nums.size());
    for(int i = 0; i< nums.size(); i++) correct.at((i+k) % nums.size()) = nums.at(i);
    

    for(int i = 0; i< nums.size(); i++) nums.at(i) = correct.at(i);
    
}



/*
One of the beeter way to do this is to reverse the whole list. Then to reverse all elements form the beginning up until the pivot point -1. Then to reverse all elements 
from the pivot point up until the end of the list. This works because when we rotate a list all elements to the left to the pivot point are placed to the right and all elements to the
right of the pivot point are placed to the left.

Run time: O(n)
Space: O(1)
*/
void rotate4(vector<int>& nums, int k) {
    if(k == 0 || nums.empty() || nums.size() == 1) return;
    int pivotIdx = k % nums.size();
        
    reverseList(0,nums.size()-1, nums);
    reverseList(0, pivotIdx-1, nums);
    reverseList(pivotIdx, nums.size()-1, nums);
        
}
    
void reverseList(int start, int end, vector<int> &nums){
    while(start < end){
        int save = nums.at(start);
        nums.at(start) = nums.at(end);
        nums.at(end) = save;
        start++;
        end--;
    }
}



/*
Another  beeter way to do this is to...
Run time: O(n)
Space: O(1)
*/
void rotate5(vector<int> &nums, int k){
    k = k % nums.size();
    int count = 0;
    for (int start = 0; count < nums.size(); start++) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % nums.size();
            int temp = nums[next];
            nums[next] = prev;
            prev = temp;
            current = next;
            count++;
        } while (start != current);
    }
}