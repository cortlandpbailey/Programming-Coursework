#include "matrix.h"
#include <vector>
using namespace std;

//finds factor to zero out vector element
double findFactor(double pivot_row, double under_row) {
    return (-1.0 * (under_row)) / pivot_row;
}
//multiples a scalar with a vector
vector<double> scalarMultiply(double factor, vector<double> vec){
    for (int i = 0; i < vec.size(); i++) { // loops through vecotr changing each element
        vec[i] *= factor;
    } return vec;
} 

//swaps two vectors in memory
void swap(vector<double>& actual_pivot_row, vector<double>& row_with_pivot) {
    vector<double> temp = actual_pivot_row; //take the original pivot row and store it
    actual_pivot_row = row_with_pivot; //swap it with the row that actually can be pivot row
    row_with_pivot = temp;
} 

//adds 2 vectors
vector<double> add(vector<double> actual_pivot_row, vector<double> under_rows) {
    for (int i = 0; i < actual_pivot_row.size(); i++) { // loops through vector adding each element to eachother
        under_rows[i] += actual_pivot_row[i];
    } return under_rows;
}

bool isInvertible(vector< vector<double> >& mat) {
    int columns = mat.size();
    if (columns == 0) { return false; } //checking the 0 case
    //checking to make sure its a square matrix
    for (int i = 0; i < columns; i++) {
        if (mat[i].size() != columns) {
        return false;
        }
    } 
    int rows = mat.size();

    //Pseudo Gaussian elimination function
    for (int pivot = 0; pivot < columns; pivot++) {
        for (int under_row = pivot; under_row < columns; under_row++) {
            if (mat[under_row][pivot] != 0) { //if we found we with a nonzero pivot, we swap it to the beginning
                swap(mat[pivot], mat[under_row]);
            for (int k = pivot+1; k < rows; k++) { //go through each row and make it 0]
                if (mat[k][pivot] == 0) { continue; } //if row already has a zero, nothing to do
                mat[pivot] = scalarMultiply(findFactor(mat[pivot][pivot],
                mat[k][pivot]), mat[pivot]); //reference function descriptions
                mat[k] = add(mat[pivot], mat[k]); //If row did not have a zero, we follow through the gaussian algorithm 4and make a zero
            }
            break;
            }
            else if (under_row == rows - 1) {//means its gone through every row and couldning find a nonzero one to switch
                return false;
            }
        }
    } return true; //finally returns true after the elimination and the diagonal numbers are all nonzero
}