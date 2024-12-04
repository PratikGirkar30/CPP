/*
Implement Heap sort to sort given set of values using max or min heap.
*/

#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
public:
    void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void buildMaxHeap(vector<int>& arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    }

    void heapSort(vector<int>& arr) {
        int n = arr.size();
        buildMaxHeap(arr, n);

        for (int i = n - 1; i >= 1; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    void printArray(const vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    HeapSort hs;
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    hs.heapSort(arr);
    cout << "Sorted array: ";
    hs.printArray(arr);

    return 0;
}
