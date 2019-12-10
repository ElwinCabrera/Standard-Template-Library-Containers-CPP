#include <vector>
using std::vector;
/*
Source: Source: Cracking the Coding interview pg. 91

Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0
*/

/*
In this approach we first check if we need to set the top row or left column to zero at the end we do this by keeping too boolean variables one for the top row and one for the left column and if there is a zero in any of these sections we set the corresponding boolean variable to true. 
Then we iterate over the rest of the matrix (not including the top row or left most column) and everytime we see a zero we set the corresponding column at the top row to zero and the coresponding row for the left column to zero.

Runtime: O(n^2) - where n is the number of integers in the matrix, we cant do better because we need to visit every element in the matrix.
Space: O(1) - no extra space is used.

*/
void zeroMatrix(vector<vector<int>> &matrix){
    
    bool firstRowZero = false;
    bool firstColZero = false;

    for(int col = 0; col < matrix.at(0).size(); ++col) if(matrix.at(0).at(col) == 0) firstRowZero = true;
    for(int row = 0; row < matrix.size(); ++row) if(matrix.at(row).at(0) == 0) firstColZero = true;
    
    for(int row = 1; row < matrix.size(); ++row){
        for(int col = 1; col < matrix.at(row).size(); ++col){
            if(matrix.at(row).at(col) == 0) {
                matrix.at(0).at(col) = 0;
                matrix.at(row).at(0) = 0;
            }
        }
    }

    for(int col = 1; col < matrix.at(0).size(); ++col){
        if(matrix.at(0).at(col) == 0) {
            for(int row = 1; row < matrix.size(); ++row) matrix.at(row).at(col) = 0;
        }
    }

    for(int row = 1; row < matrix.size(); ++row){
        if(matrix.at(row).at(0) == 0){
            for(int col = 1; col < matrix.at(0).size(); ++col) matrix.at(row).at(col) = 0;
        }
    }

    if(firstRowZero) for(int col = 0; col < matrix.at(0).size(); ++col) matrix.at(0).at(col) = 0;
    if(firstColZero) for(int row = 0 ; row < matrix.size(); ++row) matrix.at(row).at(0) = 0;
    
}