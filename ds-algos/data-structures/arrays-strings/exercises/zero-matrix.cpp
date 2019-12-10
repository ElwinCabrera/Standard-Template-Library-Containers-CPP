#include <vector>
using std::vector;

void zeroMatrix(vector<vector<int>> &matrix){
    for(int row = 1; row < matrix.size(); ++row){
        for(int col = 1; col < matrix.at(row).size(); ++col){
            if(matrix.at(row).at(col) == 0) {
                matrix.at(0).at(col) = 0;
                matrix.at(row).at(0) = 0;
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
    }
}


void setRowZero(vector<vector<int>> &matrix, int row){

}

void setColZero(vector<vector<int>> &matrix, int col){
    
}