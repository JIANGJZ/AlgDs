/*
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &vec) {
        
        auto privot = next(vec.rbegin());
        while (privot != vec.rend() && *privot >= *prev(privot)) {
            ++privot;
        }
        
        if(privot != vec.rend()) {
            auto change = find_if(vec.rbegin(), privot, bind1st(less<int>(), *privot));
            swap(*change, *privot);
            reverse(vec.rbegin(), privot);
        } else {
            reverse(vec.begin(), vec.end());
        }
        
    }
};

int main() {
    vector<int> vec = {6, 8, 7, 4, 3, 2};
    vector<int> vec2 = {1, 2, 3, 4};
    Solution s;
    s.nextPermutation(vec2);
    for(auto i : vec2) {
        cout << i << " ";
    }
}
*/
