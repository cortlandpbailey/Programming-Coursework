#include <iostream>
#include <vector>

using namespace std;

// function to swap two elements in a vector
void swap(vector<int>& v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Function to correct heap structure
void heapify_up(vector<int>& heap, int i) {
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    if (heap[parent] > heap[i]) {
        swap(heap, parent, i);
        heapify_up(heap, parent);
    }
}

// Function to insert a new element into the heap and print the heap
void insert(vector<int>& heap, int x) {
    heap.push_back(x);
    heapify_up(heap, heap.size() - 1);
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> heap;

    insert(heap, 11);
    insert(heap, 17);
    insert(heap, 3);
    insert(heap, 9);
    insert(heap, 5);
    insert(heap, 6);
    insert(heap, 14);
    insert(heap, 2);
    insert(heap, 13);
    insert(heap, 8);
    insert(heap, 1);

    return 0;
}
