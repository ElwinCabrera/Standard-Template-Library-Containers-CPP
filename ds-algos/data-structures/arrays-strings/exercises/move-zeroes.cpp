#include <vector>
using std::vector;


void moveZeroes1(vector<int>& nums){
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



void moveZeroes2(vector<int>& nums){
    if(nums.size() == 1 || nums.empty()) return ;
        
        int numZeroes = 0; 
        int emptySlotIdx = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums.at(i) == 0 ) continue;
            nums.at(emptySlotIdx++) = nums.at(i);
        }
        
        for(int i = emptySlotIdx; i <  nums.size(); i++) nums.at(i) = 0;
}



void moveZeroes3(vector<int>& nums){
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

