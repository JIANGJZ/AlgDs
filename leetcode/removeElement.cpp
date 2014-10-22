/*
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] != elem) {
                A[index++] = A[i];
            }
        }
        return index;
    }
};

class Solution2 {
public:
    long removeElement(int A[], int n, int elem) {
        return distance(A, remove(A, A+n, elem));
    }
};

int main() {
    Solution s;
    Solution2 s2;
    int arr[5] = {2, 3, 4, 2, 4};
    cout << s.removeElement(arr, 5, 2) << endl;
    cout << s2.removeElement(arr, 4, 2) << endl;
}
*/