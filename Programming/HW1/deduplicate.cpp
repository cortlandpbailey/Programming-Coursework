//No Libraries used
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