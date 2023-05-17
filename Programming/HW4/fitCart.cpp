#include <iostream>
#include <vector>
using namespace std;

// given items with volume and price, compute max price for a max volume cart
vector<bool> fitCart(vector<int>& volumes, vector<int>& prices, int maxVolume) {
    int n = volumes.size();                         
    vector<vector<int>> items(n + 1, vector<int>(maxVolume + 1, 0));     // create matrix to hold each item which is the max that will fit the volume
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= maxVolume; j++) {                      // iterate through the matrix, inserting each combination of items with which fit the cart
            if (volumes.at(i-1) > j)
                items.at(i).at(j) = items.at(i - 1).at(j);          // if the item does not fit, don't include it and assign the current locations value to the previous one
            else
                items[i][j] = max(items.at(i - 1).at(j), items.at(i - 1).at(j - volumes.at(i - 1)) + prices.at(i - 1));     // if it does fit, see if its value is greater than the last one. If it is, write that value in. Otherwise write the value of the previous
        }
    }
    vector<bool> selected(n, false);        // vector for holding the index of selected items
    int i = n;
    int j = maxVolume;
    while (i > 0 && j >0) {                 // starting at the bottom, go through the matrix and select each unique value and place it into the selected vector
        if (items.at(i).at(j) != items.at(i-1).at(j)) {
            selected[i-1] = true;     // choose the current item
            j -= volumes.at(i - 1);         // decrement the volume by item emplaced size
        }
        i--;
    }
    return selected;
}