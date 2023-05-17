#include <iostream>
void bubbleSort(int nums[], int n) {

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - 1 - i; j++){
            if (nums[j+1] > nums[j]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

void quickSort(int nums[], int n) {
    int start = nums[0];
    int end = nums[n - 1];
    if (n = 1)
        return;
    int s = start+1;      // Establish partition point
    int e = end;
    int temp;
    while (s<=e) {
        if (nums[s] <= nums[start])
            s++;
        if (nums[e]> nums[start]) 
            e--;
        if (s <= e) {
            temp = nums[s];
            nums[s] = nums[e];
            nums[e] = temp;
        }
    }
    temp = nums[start];
    nums[start] = nums[e];
    nums[e] = temp;

    int nums_lower[n - 1 - e] = {nums[]};
    quickSort(nums[s, end], n - s);
    quickSort(nums[0, s - 1], s);
}



int deduplicate(int nums[], int n) {
    int r = 0;
    for (int i = 0; i < n - 1; i++){
        int temp = nums[i];
        for (int j = i+1; j < n-1; j++) {
            if (temp == nums[j]){
                // Shift down the array and increment the return
                r++;
                for (int k = j; k < n-1; k++){
                    nums[k] = nums[k + 1];
                }
            }
        }
    }
    return n-r;
}

bool checkValid(char exp[]){
    
}

int main() {

    int x[] = { 1, 5, 7, 3, 10, 42, 0, 3, 13 };
    quickSort(x, 9);
    std::cout << x << std::endl;
    int c = deduplicate(x, 9);
    std::cout << x << std::endl;
    std::cout << c << std::endl;
    int z;
    std::cin >> z;

    return 0; 
}
