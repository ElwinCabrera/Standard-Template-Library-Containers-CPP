#include<vector>
#include<math.h>
using std::vector;
using std::max;

int maxSubArray(vector<int>& nums) {
        
    int currMax = nums.at(0);
    int localSum = nums.at(0);
    for(int i = 1; i < nums.size(); i++){
        localSum = max(localSum + nums.at(i), nums.at(i));
        currMax = max(localSum, currMax);
    }
    return currMax;
        
}