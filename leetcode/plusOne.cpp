/*
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& arr) {
        add(arr, 1);
        return arr;
    }
private:
    void add(vector<int>& arr, int digit) {
        int c = digit;
        for_each(arr.rbegin(), arr.rend(), [&c](int& d){
            d += c;
            c = d / 10;
            d %= 10;
        });
        if (c > 0) {
            arr.insert(arr.begin(), 1);
        }
    }
};

int main() {
    vector<int> vec = {9, 9, 9, 9};
    Solution s;
    s.plusOne(vec);
    for(auto i : vec) {
        cout << i << endl;
    }
}
*/