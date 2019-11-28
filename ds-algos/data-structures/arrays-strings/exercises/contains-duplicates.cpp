/*

Original: https://leetcode.com/problems/contains-duplicate/

Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true

Example 2:

Input: [1,2,3,4]
Output: false

Example 3:

Input: [1,1,1,3,3,4,3,2,4,2]
Output: true


*/

#include <vector>
#include <algorithm>
using std::vector;
using std::sort;

/*
This solution is pretty straight forward. First, you sort the original array. After the array is sorted then you can simply iterate through the list checking if the number 
previous is the same as the number you are checking now and if they are the same return true.

Runtime : O(nlogn),because of the sorting
Space: O(n) or even O(1) depending what sorting you use (heap sort)
*/
bool containsDuplicate(vector<int>& nums) {
    if(nums.empty() || nums.size()==1) return false;
    sort(nums.begin(), nums.end());
        
    for(int i = 1 ; i < nums.size(); i++){
        if(nums.at(i) == nums.at(i-1)) return true;
    }
    return false;
}