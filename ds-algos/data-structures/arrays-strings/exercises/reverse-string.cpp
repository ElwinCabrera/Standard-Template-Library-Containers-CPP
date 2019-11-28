#include <iostream>
#include <vector>

using std::vector;


vector<int> reverseArray1(vector<int> arr){
    vector<int> result;
    for(int i = arr.size()-1; i>=0; i--){
        result.push_back(arr.at(i));
    }
    return result;
}

/* in place using swapping*/
vector<int> reverseArray2(vector<int> arr){
    
    int start = 0;
    int end = arr.size()-1;
    while(start < end){
        int mem = arr.at(start);
        arr.at(start) = arr.at(end);
        arr.at(end) = mem;

        start++;
        end--;
    }
    return arr;
}