#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "matrix.h"
using namespace std;

// Function Declarations:
void loadInputFile(const char* filename, vector< vector<int>>&);


//Main
int main() {
    vector<vector<int>> net_mat;
    loadInputFile("netlist.txt", net_mat);

    cout << net_mat.at(0).at(0) << " " << net_mat.at(0).at(1) << " " << net_mat.at(0).at(2) << endl;
    cout << net_mat.at(1).at(0) << " " << net_mat.at(1).at(1)<< " " << net_mat.at(1).at(2) << endl; 
    cout << net_mat.at(2).at(0) << " " << net_mat.at(2).at(1)<< " " << net_mat.at(2).at(2) << endl;   
    return 0;
}


// Function Definitions

// Load input file to a matrix:
void loadInputFile(const char* filename, vector< vector<int>>& input_matrix) {
    fstream file(filename);
    char* temp;
    //int c = file.peek();
    file.getline(temp, '|');
    if (temp[0] !='v' || temp[0]!='r')
        return;
    while(file.getline(temp, '|')){
        vector<int> v;
        int i =0;
        int c = file.peek();
        if (c== EOF)
            return;
        else if (c == 'v' || c == 'r') {
            input_matrix.push_back((v));
            file.getline(temp, '|');
        }
        else {
            i++;
            v.push_back(stoi(temp));
        }
            
    }
    

    return;
}

