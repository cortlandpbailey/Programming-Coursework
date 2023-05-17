#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int determinant(vector<vector<double>>& mat, int size) {
    int det = 0;
    vector<vector<double>> temp(size, vector<double>(size));
    if(size==2) {
        return ((mat.at(0).at(0) * mat.at(1).at(1)) - (mat.at(1).at(0) * mat.at(0).at(1)));
    }
    else {
        for (int i = 0; i < size; i++){
            int temp_x = 0;
            for (int j = 1; j < size; j++){
                int temp_y = 0;
                for (int k = 0; k < size; k++){
                    if (k == i)
                        continue;
                    temp.at(temp_x).at(temp_y) = mat.at(j).at(k);
                    temp_y++;
                }
                temp_x++;
            }

            det = det + (pow(-1, i) * mat.at(0).at(i) * determinant(temp, size-1));
        }
    }
    return det;
}
bool isInvertible(vector<vector<double>>& mat){
    // Check for empty matrix
    if (mat.size() == 0)
        return false;

    // Check for non-square matrix
    for (int i = 0; i < mat.size(); i++){
        if (mat.at(i).size() != mat.size())
            return false;
    }

    // calc the determinant and see if it is 0 or anything else. 
    int det = determinant(mat, mat.size());
    if (det==0)
        return false;
    else
        return true;
}


int main() {
    vector<vector<double>> test_vec =
        {{1,0,1},
         {0,1,0},
         {10,0,1}};

    bool test = isInvertible(test_vec);
    if (test==true)
        cout << "The matrix is invertible"<< endl;
    else
        cout << "The matrix is not invertible" << endl;
    return 0;
}