/*

The following example was taken from HackerRank you can find the original at https://www.hackerrank.com/challenges/2d-array/problem

Given a 6 x 6 2D Array, arr:

1 1 1 0 0 0
0 1 0 0 0 0
1 1 1 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

We define an hourglass in A to be a subset of values with indices falling in this pattern in arr's graphical representation:

a b c
  d
e f g

There are 16 hourglasses in arr, and an hourglass sum is the sum of an hourglass' values. Calculate the hourglass sum for every hourglass in
arr, then print the maximum hourglass sum.

For example, given the 2D array:

-9 -9 -9  1 1 1 
 0 -9  0  4 3 2
-9 -9 -9  1 2 3
 0  0  8  6 6 0
 0  0  0 -2 0 0
 0  0  1  2 4 0

We calculate the following 16 hourglass values:

-63, -34, -9, 12, 
-10, 0, 28, 23, 
-27, -11, -2, 10, 
9, 17, 25, 18

Our highest hourglass value is 28 from the hourglass:

0 4 3
  1
8 6 6

Input Format

Each of the 6 lines of inputs arr[i] contains 6 space-separated integers arr[i][j].

Constraints

* -9 <= arr[i][j] <= 9
* 0 <= i,j <= 5

Output Format

Print the largest (maximum) hourglass sum found in arr.

*/






#include <iostream>
#include <vector>
#include <limits.h>

using std::vector;


bool isValidHourglassShape(int row, int col, vector<vector<int>> arr){
    if(row + 2 < arr.size() && col + 2 < arr.at(row).size()) return true;
    return false;
}

int getSum(int row, int col, vector<vector<int>> arr){
    int sum = 0;
    for(int c = col; c < col+3; c++) {
        sum += arr.at(row).at(c);
        sum += arr.at(row+2).at(c);
    }
    sum += arr.at(row+1).at(col+1);
    return sum;
}

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
// for every element I can check if at taht position there is a valid hourglass 
//(its within bounds). Then I can calculate the sum and update the max sum it the 
//new sum is bigger

    int currMax = INT_MIN;
    for(int row = 0; row < arr.size(); row++){
        for(int col = 0; col < arr.at(row).size(); col++){
            if(isValidHourglassShape(row, col, arr)){
                //printf("within bounds r %d c %d\n", row, col);
                int localMax = getSum(row, col, arr);
                if(localMax > currMax) currMax = localMax;
            }
        }
    }

    return currMax; 

}