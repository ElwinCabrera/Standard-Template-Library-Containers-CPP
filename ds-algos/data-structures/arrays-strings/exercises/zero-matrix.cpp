#include <vector>
using std::vector;
/*

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