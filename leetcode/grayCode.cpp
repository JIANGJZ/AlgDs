/*
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        result.reserve(1 << n);
        
        for (int i = 0; i < result.capacity(); i++) {
            result.push_back(binary_to_gray(i));
        }
        return result;
    }
private:
    static unsigned int binary_to_gray(int n) {
        return n^(n >> 1);
    }
};

class Solution2 {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        result.reserve(1 << n);
        result.push_back(0);
        for (int i = 0; i < n; i++) {
            const int highest_bit = 1 << i;
            for (int j = (int)result.size()-1; j > 0; j--) {
                result.push_back(highest_bit | result[j]);
            }
        }
        return result;
    }
};

void show(int n) {
    cout << n << " ";
}

int main() {
    Solution s;
    vector<int> grayCode = s.grayCode(2);
    for_each(grayCode.begin(), grayCode.end(), show);
}
*/