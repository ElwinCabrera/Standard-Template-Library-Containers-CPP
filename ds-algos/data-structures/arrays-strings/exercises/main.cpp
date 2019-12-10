#include "is-unique.cpp"
#include "check-permutation.cpp"
#include "urlify.cpp"
#include "palindrome-permuation.cpp"
#include "valid-parentheses.cpp"
#include "one-away.cpp"
#include "string-compression.cpp"
#include "rotate-matrix.cpp"
#include "zero-matrix.cpp"

void printMatrix(vector<vector<int>> &matrix);

int main(int argc, char **argv){

    vector<vector<int>> matrix = {
        {1,9,3,9},
        {5,6,6,8},
        {0,10,11,12},
        {13,14,15,16}
    };
    printMatrix(matrix);
    zeroMatrix(matrix);
    printMatrix(matrix);

    

    return 0;
}

void printMatrix(vector<vector<int>> &matrix){
    cout << "["<<std::endl;

    for(vector<int> vect: matrix){
        cout << "  [";
        for(int i: vect){
            cout << i <<" ";
        }
        cout << "]\n";
    }
    cout << "]\n";
}