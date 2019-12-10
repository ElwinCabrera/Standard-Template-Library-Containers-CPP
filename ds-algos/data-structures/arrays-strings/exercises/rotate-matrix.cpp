#include<vector>
using std::vector;

/*
Given an image represented by an N x N matrix, where each pixel in the image is 4 bytes (an integer), write a method to rotate the image by 90 degrees. Can you do this in place?

*/

/*
One approach to this problem is to think what happens when you rotate a matrix. For a 90 degree rotation the columns switch with the rows for every column that there is in the matrix.
We can do this by starting with the top row and switching counter-clockwise until the top row is positioned at the right column. 

Runtime: O(n^2) where n is the size of the matrix, we cant do better than this because we have to touch all numbers in matrix. 
Space: O(1) 
*/
void rotateMatrix(vector<vector<int>> &matrix){

    for(int layer = 0; layer < matrix.size() /2; ++layer){
        int last = matrix.size() - layer - 1;
        for(int i = layer; i < last; ++i){
            int offset = i - layer;
            int tmp = matrix.at(layer).at(i);

            // left -> top
            matrix.at(layer).at(i) = matrix.at(last-offset).at(layer);

            //bottom -> left
            matrix.at(last-offset).at(layer) = matrix.at(last).at(last-offset);

            // right -> bottom
            matrix.at(last).at(last - offset) = matrix.at(i).at(last);

            // top -> right
            matrix.at(i).at(last) = tmp;
        }
    }
}