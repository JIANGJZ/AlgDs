/*
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

class Solution {
public:
    long removeDuplicate(int A[], int n) {
        if (n == 0) {
            return 0;
        }
        
        int index = 0;
        for (int i = 1; i < n; i++) {
            if (A[index] != A[i]) {
                A[++index] = A[i];
            }
        }
        return index + 1;
    }
};

class Solution2 {
public:
    long removeDuplicate(int A[], int n) {
        return distance(A, unique(A, A + n));
    }
};

class Solution3 {
public:
    long removeDuplicate(int A[], int n) {
        return removeDuplicate(A, A + n, A) - A;
    }
    
private:
    template<typename InIt, typename OutIt>
    OutIt removeDuplicate(InIt first, InIt last, OutIt output) {
        while (first != last) {
            *(output++) = *first;
            first = upper_bound(first, last, *first);
        }
        
        return output;
    }
};

int main() {
    int arr[5] = {1, 3, 3, 4, 4};
    Solution s;
    cout << s.removeDuplicate(arr, 5) << endl;
    Solution2 s2;
    cout << s2.removeDuplicate(arr, 5) << endl;
    Solution3 s3;
    cout << s3.removeDuplicate(arr, 5) << endl;
    
}
*/
