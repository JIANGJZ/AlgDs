/*
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class Solution
{
public:
    int singleNum(int A[], int size) {
        const int bit_len = sizeof(int) * 8;
        int count[bit_len];
        fill_n(count, bit_len, 0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < bit_len; j++) {
                count[j] += (A[i] >> j) & 1;
                count[j] %= 3;
            }
        }
        
        int result = 0;
        for (int i = 0; i < bit_len; i++) {
            result += (count[i] << i);
        }
        
        return result;
    }
};

//二进制模拟三进制
class Solution2
{
public:
    int singleNum(int A[], int size) {
        int one = 0;
        int two = 0;
        int three = 0;
        for (int i = 0; i < size; i++) {
            two |= (one & A[i]);
            one ^= A[i];
            three = ~(one & two);
            one &= three;
            two &= three;
        }
        
        return one;
    }
    
};

int main() {
    int arr[7] = {2, 1, 1, 1, 3, 3, 3};
    Solution s;
    Solution2 s2;
    cout << s.singleNum(arr, 7) << endl;
    cout << s2.singleNum(arr, 7) << endl;
}
*/