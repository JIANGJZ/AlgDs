/*
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicate(int A[], int n) {
        if (n <= 2) {
            return n;
        }
        int index = 2;
        for (int i = 2; i < n; i++) {
            if (A[i] != A[index - 2]) {
                A[index++] = A[i];
            }
        }
        return index;
    }
};

class Solution2 {
public:
    int removeDuplicate(int A[], int n) {
        if (n <= 2) {
            return n;
        }
        int index = 1;
        for (int i = 1; i < n; i++) {
            if (A[i] == A[i - 1] && A[i] == A[i + 1] && i > 0 && i < n - 1) {
                continue;
            }else{
                A[index++] = A[i];
            }
        }
        return index;
    }
};

int main() {
    int arr[10] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 3};
    Solution s;
    cout << s.removeDuplicate(arr, 7) << endl;
    Solution2 s2;
    cout << s2.removeDuplicate(arr, 7);
}
*/