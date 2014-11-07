/*
#include <iostream>
#include <numeric>

using namespace std;

class Solution
{
public:
    int findSingle(int A[], int size) {
        int x = 0;
        for (int i = 0; i < size; i++) {
            x ^= A[i];
        }
        
        return x;
    }
};

class Solution2 {
public:
    int findSingle(int A[], int size) {
        return accumulate(A, A+size, 0, bit_xor<int>());
    }
};

int main()
{
    int A[5] = {1,2,1,2,3};
    Solution2 s2;
    Solution s;
    cout << s.findSingle(A, 5) << endl;
}
*/