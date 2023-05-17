#include <vector>
using namespace std;

class matrix {
public:
    //finds factor to zero out vector element
    double findFactor(double pivot_row, double under_row);

    //multiples a scalar with a vector
    vector<double> scalarMultiply(double factor, vector<double> vec);

    //swaps two vectors in memory
    void swap(vector<double> &actual_pivot_row, vector<double> &row_with_pivot);
    //adds 2 vectors
    vector<double> add(vector<double> actual_pivot_row, vector<double> under_rows);
    bool isInvertible(vector<vector<double>> &mat);
private:
};
